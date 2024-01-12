#!/usr/bin/env python3
import statistics
from tqdm import tqdm
import numpy as np
import tensorflow as tf
from tensorflow import keras
from keras import layers

import pickle
import random

from settings import *

train_X = None
train_Y = None
test_X = None
test_Y = None

best_accuracy = 99999

# GOAL: train RNN on STDDEV
def read_data():
    global train_X, train_Y, test_X, test_Y

    data = None

    with open(OUTPUT_FOLDER + '/data.pickle', 'rb') as handle:
        data = pickle.load(handle)


    iat_features = []
    labels = []

    for key, val in data["train"].items():
        iat_features.extend(val["samples"])
        labels.extend(val["labels"])

    # ML data
    # Features will be one smaller sice stddev requires at least two values
    features = []

    # loop over loaded streams
    print("Reading Stream data ...")

    # TODO: maybe use lambda to make more efficient
    for i in tqdm(range(0,len(iat_features))):
    #for i in tqdm(range(0,100)):
        stream = iat_features[i]

        feature = []

        # loop over all timestamps
        # Variance requires at least two values, so skip first one
        for j in range(1,len(stream)):
            vals = stream[0:j + 1]

            stddev = statistics.stdev(vals)
            mean = statistics.mean(vals)

            norm_stddev = stddev/mean

            feature.append(norm_stddev)
        
        # LSTM input has shape (samples, timesteps, features)
        # Since each timestep gets 1 STDEV as feature, the shape has to be (1,n)
        # This is achieved by transforming the list into a column vector
        features.append(np.array([feature]).T)

        labels[i] = np.delete(labels[i],0)

    # Store coefficients of variation as array
    #features = np.asarray(features)

    full = list(zip(features, labels))

    random.seed(SEEDS[0])
    random.shuffle(full)

    features, labels = zip(*full)

    # Split array for validation set
    split_index = int((1-VALIDATION_SPLIT) * len(features))
    train_X = tf.ragged.constant(features[:split_index])
    train_Y = tf.ragged.constant(labels[:split_index])
    test_X = tf.ragged.constant(features[split_index+1:])
    test_Y = tf.ragged.constant(labels[split_index+1:])

def train_single_model():
    # Build Model
    model = keras.Sequential()

    # Input
    # Shape is None (timesteps), and 1 (Features per Timestep)
    model.add(layers.Input(shape=[None,1],dtype="float",ragged=True))

    # RNN
    model.add(layers.LSTM(200,activation='relu',return_sequences=True))
    model.add(layers.LSTM(400,activation='relu',return_sequences=True))
    model.add(layers.LSTM(400,activation='relu',return_sequences=True,dropout=0.25,recurrent_dropout=0.25))
    model.add(layers.LSTM(200,activation='relu',return_sequences=True,dropout=0.25,recurrent_dropout=0.25))
    model.add(layers.LSTM(1,activation='sigmoid',return_sequences=True))

    # Compile using give nloss function
    model.compile(
        optimizer="adam",
        loss="binary_crossentropy", # Best loss function for binary classification
        metrics=[tf.keras.metrics.BinaryCrossentropy()]
    )

    callback = keras.callbacks.EarlyStopping(patience=5,restore_best_weights=True,min_delta=0.0001)

    # Fit model
    model.fit(train_X,train_Y,epochs=100,validation_data=(test_X, test_Y),callbacks=[callback])

    _, accuracy = model.evaluate(test_X, test_Y)

    return model,accuracy



def main():
    best_accuracy = 999999
    for i in range(0,50):

        print("##### RUN NUMBER {} #####".format(i))
        model, accuracy = train_single_model()

        if accuracy < best_accuracy:
            best_accuracy = accuracy
            model.save("data/best.keras")
            print("New best: {} ---------------------".format(accuracy))


if __name__ == "__main__":
    read_data()
    main()
