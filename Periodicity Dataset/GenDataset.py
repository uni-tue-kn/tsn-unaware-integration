from lib import sample_new_stream, sample_near_periodic_stream
import numpy as np
from tqdm import tqdm
import os
import random
from multiprocessing import Process, Manager
import pickle
from settings import *

def sample_stream_data(period_range, stream_count, stream_lengths, return_dict):
    """Generates stream data according to global constants and passed parameters.

    Args:
        period_range (range): Range from which the streams periods are sampled
        stream_count (int): Amount of streams per class
        stream_lengths (list): List of possible stream lengths as ints
        return_dict (dict): Dict for storing results. Use multiprocessing.Manager().dict() when working with processes.
    """
    
    # Generate periodic streams
    drawn_periods = [random.randrange(
        period_range[0], period_range[-1]) for x in range(0, stream_count)]
    samples = []
    labels = []
    lengths = []
    stddevs = []
    
    for i in tqdm(range(0, stream_count), "Generating {} periodic streams".format(stream_count)):

        # get drawn period
        period = np.around(drawn_periods[i])

        # Get random length of stream, equally distributed
        length = np.random.choice(stream_lengths)

        # Get standarddev in % for this stream
        nstddev = np.random.choice(PERIODIC_STDDEV) / 100
        
        # Sample stream and labels
        #sample, label = sample_stream(period * PERIOD_FACTOR, nstddev, length, is_periodic=True)
        sample, label = sample_new_stream(period * PERIOD_FACTOR, nstddev, 1, length, True)

        samples.append(np.asarray(np.around(sample, ROUND_DIGITS)))
        labels.append(np.asarray(label))
        lengths.append(1)
        stddevs.append(nstddev)


    # Store stream information
    return_dict["periodic"] = {
        "type":0,
        "samples": samples,
        "labels": labels,
        "pattern_length": lengths,
        "stddevs": stddevs
    }

    # Generate non-periodic streams, also due non-periodic streams that look like patterns
    drawn_periods = [random.randrange(
        period_range[0], period_range[-1]) for x in range(0, stream_count)]
    samples = []
    labels = []
    lengths = []
    stddevs = []
    
    for i in tqdm(range(0, stream_count), "Generating {} non-periodic streams".format(stream_count)):

        # get drawn period
        period = np.around(drawn_periods[i])

        # Get random length of stream, equally distributed
        length = np.random.choice(stream_lengths)

        # Get standarddev in % for this stream
        nstddev = np.random.choice(APERIODIC_STDDEV) / 100
        
        # Sample stream and labels
        #sample, label = sample_stream(period * PERIOD_FACTOR, nstddev, length, is_periodic=False)
        sample, label = sample_new_stream(period * PERIOD_FACTOR, nstddev, 1, length, False)
        
        samples.append(np.asarray(np.around(sample, ROUND_DIGITS)))
        labels.append(np.asarray(label))
        lengths.append(1)
        stddevs.append(nstddev)

    # Store stream information
    return_dict["nonperiodic"] = {
        "type":1,
        "samples": samples,
        "labels": labels,
        "pattern_length": lengths,
        "stddevs": stddevs
    }

    # Generate periodic pattern streams
    drawn_periods = [random.randrange(
        period_range[0], period_range[-1]) for x in range(0, stream_count)]
    samples = []
    labels = []
    lengths = []
    stddevs = []

    for i in tqdm(range(0, stream_count), "Generating {} periodic pattern streams".format(stream_count)):

        # get drawn period
        period = np.around(drawn_periods[i])

        # Get random length of stream, equally distributed
        length = np.random.choice(stream_lengths)

        pattern_length = random.choice(PACKETS_PER_PATTERN)

        # Get standarddev in % for this stream
        nstddev = np.random.choice(PERIODIC_STDDEV) / 100
        
        # Sample stream and labels
        #sample, label, pattern_length = sample_periodic_pattern(
        #            period * PERIOD_FACTOR, nstddev, PACKETS_PER_PATTERN, length, is_periodic=True)
        sample, label = sample_new_stream(period * PERIOD_FACTOR, nstddev, pattern_length, length, True)

        samples.append(np.asarray(np.around(sample, ROUND_DIGITS)))
        labels.append(np.asarray(label))

        lengths.append(pattern_length)
        stddevs.append(nstddev)

    # Store stream information
    return_dict["pattern"] = {
        "type":2,
        "samples": samples,
        "labels": labels,
        "pattern_length": lengths,
        "stddevs": stddevs
    }

    # Generate near periodic streams
    drawn_periods = [random.randrange(
        period_range[0], period_range[-1]) for x in range(0, stream_count)]
    samples = []
    labels = []
    lengths = []
    stddevs = []

    for i in tqdm(range(0, stream_count), "Generating {} near periodic streams".format(stream_count)):

        # get drawn period
        period = np.around(drawn_periods[i])

        # Get random length of stream, equally distributed
        length = np.random.choice(stream_lengths)

        # Get standarddev in % for this stream
        nstddev = np.random.choice(PERIODIC_STDDEV) / 100
        
        # Sample stream and labels
        sample,label = sample_near_periodic_stream(period * PERIOD_FACTOR, PERIODIC_STDDEV[-1] / 100, length)

        samples.append(np.asarray(np.around(sample, ROUND_DIGITS)))
        labels.append(np.asarray(label))
        lengths.append(1)
        stddevs.append(nstddev)

    # Store stream information
    return_dict["near"] = {
        "type":3,
        "samples": samples,
        "labels": labels,
        "pattern_length": lengths,
        "stddevs": stddevs
    }

    return


def process_gen_dataset(seed, period_range, stream_count, stream_lengths, return_dict):
    """Target function for stream data generation. Resulting data is returned in return_dict under the key passed as function parameter.
    Uses global cosntants STREAM_COUNT, STREAM_LENGTHS, STREAM_TYPES.
    Return dict will contain the keys features, labels, periods, stream_types und the parent key given as parameter.

    Args:
        seed (int): Seed for random initialization
        period_range (range): Range from which the streams periods are sampled
        stream_count (int): Amount of streams to generate
        stream_lengths (list): List of possible stream lengths as ints
        return_dict (dict): Dict for storing results. Use multiprocessing.Manager().dict() when working with processes.
    """

    # Seed random number generation
    random.seed(seed)
    np.random.seed(seed)

    # Call function that samples dataset
    sample_stream_data(period_range, stream_count,stream_lengths, return_dict)


def create_proc(seed, period_range,return_dict):
    """Create a process object for data generation.

    Args:
        seed (int): Seed for random initialization
        period_range (range): Range from which the streams periods are sampled
        return_dict (dict): Dict for storing results. Use multiprocessing.Manager().dict() when working with processes.
        key (str): Key to store data under in dict.

    Returns:
        multiprocessing.Process: Process object
    """
    return Process(
        target=process_gen_dataset, 
        args=(
        seed, 
        period_range, 
        STREAM_COUNT, 
        STREAM_LENGTHS, 
        return_dict)
        )
    

def generate_data(seeds):
    """Function that generates data via processes 

    Args:
        seeds (list): Seeds to use for processes

    Returns:
        dict: Dict containing results from all processes.
    """

    # Create dictionary that includes shared access control for the processes
    # Will be used to fetch all return values
    train_dict = Manager().dict()
    test_dict = Manager().dict()

    # Create generation processes
    train_proc = create_proc(seeds[0],PERIOD_RANGE,train_dict)
    test_proc = create_proc(seeds[1],PERIOD_RANGE,test_dict)

    # Start and wait until processes finish
    train_proc.start()
    test_proc.start()
    train_proc.join()
    test_proc.join()

    results = {
        "train": dict(train_dict.copy()),
        "test": dict(test_dict.copy())
    }

    return results

                    
def main():
    # Check if folder exists
    if not os.path.isdir(OUTPUT_FOLDER):
        os.mkdir(OUTPUT_FOLDER)

    print("Generating randomly drawn IATs... .Outputting to: {}/data.pickle".format(OUTPUT_FOLDER))

    # Generate data
    data = generate_data(SEEDS[0:2])

    with open(OUTPUT_FOLDER + '/data.pickle', 'wb') as handle:
        pickle.dump(data, handle, protocol=pickle.HIGHEST_PROTOCOL)


if __name__ == "__main__":
    main()
