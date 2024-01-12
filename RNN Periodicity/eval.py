import statistics
from tqdm import tqdm
import os 
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'

import numpy as np
import tensorflow as tf

from settings import *

import pickle
import random
import matplotlib.pyplot as plt
import sys
import json

test_X = None
test_Y = None
r_test_X = None
r_test_Y = None
RNN_Out = None

# GOAL: train RNN on STDDEV
def read_data(types=None,length_limit=sys.maxsize,min_length=0):
    global test_X, test_Y, r_test_X , r_test_Y

    data = None

    with open(OUTPUT_FOLDER + '/data.pickle', 'rb') as handle:
        data = pickle.load(handle)


    iat_features = []
    labels = []

    if types is None:
        for key, val in data["test"].items():
                iat_features.extend(val["samples"])
                labels.extend(val["labels"])
    else:
        for key, val in data["test"].items():
            if val["type"] in types:
                iat_features.extend(val["samples"])
                labels.extend(val["labels"])


    array_length = len(iat_features)
    i = 1

    while i < (array_length - 1):
        sample_length = len(iat_features[i])

        if sample_length > length_limit or sample_length < min_length:
            iat_features.pop(i)
            labels.pop(i)
            array_length -= 1
            continue

        
        i += 1

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

    random.seed(SEEDS[1])
    random.shuffle(full)

    test_X, test_Y = zip(*full)

    r_test_X = tf.ragged.constant(test_X)
    r_test_Y = tf.ragged.constant(test_Y)

def get_run_metrics(labels, predictions, max_length = 0, threshold = 0.99):

    # Set to max array size if no length is given
    if max_length == 0:
        max_length = len(predictions)

    # Stores TP, FP, .. count after each new packet arrival
    res = {
        "TP": [0]*max_length,
        "FP": [0]*max_length,
        "TN": [0]*max_length,
        "FN": [0]*max_length
    }

    preds = predictions > threshold

    for i in range(0,max_length):

        if i >= len(labels):
            break

        label = (labels[i] == 1)
    
        # If prediciton is > threshold, then prediciton is periodic otherwise
        # it is non-periodic

        # RNN output is two dim array (m,n)
        # m: number of timesteps
        # n: output per timestep, so n = 1 for this case
        # hence the [0] index is needed
        prediciton_label = preds[i][0]

        if prediciton_label == True:
            # Prediction is periodic

            if prediciton_label == label:
                # Correct prediction as periodic
                res["TP"][i] += 1
            else:
                # Wrong prediction as periodic
                res["FP"][i] += 1

        else:
            # Prediction is non-periodic

            if prediciton_label == label:
                # Corret prediction as non-periodic
                res["TN"][i] += 1

            else:
                # wrong prediction as non-periodic
                res["FN"][i] += 1

    return res

# GOAL: train RNN on STDDEV
def predict(confidences=[0.9]):
    global RNN_Out, test_X
    import keras
    # Load Model
    model = keras.models.load_model("data/best.keras")

    # Apply model to dataset
    RNN_Out = model.predict(r_test_X).numpy()

    # Data present:
    # test_X - input features
    # test_Y - labels for input features
    # RNN_Out - labels from NN


    max_length = STREAM_LENGTHS[-1]

    return_data = {}

    for conf in confidences:
        metrics = {
            "TP": [0]*max_length,
            "FP": [0]*max_length,
            "TN": [0]*max_length,
            "FN": [0]*max_length
        }

        # Iterate over test data labels
        for i in range(0,len(test_Y)):
            # Get TP, FP, ... from this sample
            run_metrics = get_run_metrics(test_Y[i], RNN_Out[i], max_length=max_length, threshold=conf)

            # Adds values of the same keys from the two dictionaries
            for key in metrics:
                for i in range(0,len(run_metrics[key])):
                    metrics[key][i] = metrics[key][i] + run_metrics[key][i]


        # accuracy = (TP + TN) / n
        # Problem: n changes over time
        accuracy = [0]*max_length
        for i in range(0,max_length):
            n = metrics["TP"][i] + metrics["TN"][i] + metrics["FP"][i] + metrics["FN"][i]
            try:
                accuracy[i] = (metrics["TP"][i] + metrics["TN"][i]) / n
            except ZeroDivisionError:
                accuracy[i] = 0

        # recall = TP / ( TP + FN )
        recall = [0]*max_length
        for i in range(0,max_length):
            try:
                recall[i] = metrics["TP"][i] / (metrics["TP"][i] + metrics["FN"][i])
            except ZeroDivisionError:
                recall[i] = 0

        # precision = TP / ( TP + FP)
        precision = [0]*max_length
        for i in range(0,max_length):
            try:
                precision[i] = metrics["TP"][i] / (metrics["TP"][i] + metrics["FP"][i])
            except ZeroDivisionError:
                precision[i] = 0


        # f1 score = (2 * precision * recall) / (precision + recall)
        f1_score = [0]*max_length
        for i in range(0,max_length):
            try:
                f1_score[i] = (2*precision[i]*recall[i])/(precision[i]+recall[i])
            except ZeroDivisionError:
                f1_score[i] = 0

        data = {
            "accuracy": accuracy,
            "recall": recall,
            "precision": precision,
            "f1_score": f1_score
        }

        return_data[conf] = data

    return return_data



def plot_data():
    for i in range(0,200):
        plt.plot(range(0,len(test_X[i])), test_X[i])
    plt.savefig("eval.png")



def pred1ict_example(example_series):
    import keras
    feature = []

    # loop over all timestamps
    # Variance requires at least two values, so skip first one
    for j in range(1,len(example_series)):
        vals = example_series[0:j + 1]
        stddev = statistics.stdev(vals)
        mean = statistics.mean(vals)
        norm_stddev = stddev/mean
        feature.append(norm_stddev)

    model = keras.models.load_model("data/adam_new_0_08_loss.keras")

    feature = [np.array([feature]).T]

    test_X = tf.ragged.constant(feature)

    # Apply model to dataset
    RNN_Out = model.predict(test_X).numpy()

    print(RNN_Out)


if __name__ == "__main__":

    confidences = np.arange(0.1,0.99,0.05)
    confidences = [round(x,2) for x in confidences]
    confidences.append(0.99)
    read_data([0,1,2,3])

    data = {}
    data = predict(confidences=confidences)

    with open("data/NN_eval.json","w") as outfile:
        outfile.write(json.dumps(data))
