import numpy as np
import random
from decimal import *
import statistics
import pickle

from settings import *


def sample_new_stream(period, norm_stddev, packets_per_pattern, count,is_periodic,pattern_iat_upper=1,pattern_iat_lower=0):
    """Sample a pattern based stream by using a periodic stream drawn from a normalized distribution as basis.

    Args:
        period (float): Target period between patterns
        norm_stddev (float): Normalized standard deviation for distribution
        packets_per_pattern (int): Number of packets per repeating pattern
        count (int): Number of samples for stream
        is_periodic (bool): If strea mto generate should be periodic or aperiodic
        pattern_iat_upper (float): Default 1, upper bound of factor applied to IATs for patterns
        pattern_iat_lower (float): Default 0, lower bound of factor applied to IATs for patterns

    Returns:
        list,list: IATs and labels
    """

    # Calculate stddev
    stddev = norm_stddev*period

    # Draw periods from normal distribution
    iats = np.random.normal(period, stddev, (count))

    # Ensure that no negative arrivals
    # A negative arrival will be treated as burst
    iats[iats<0] = PERIOD_FACTOR

    # TODO: labels should maybe be different?
    # Not periodic from hte beginning on
    if is_periodic:
        # Initialize labels as 0
        labels = np.zeros((count))

        # Generate packets_per_pattern - 1 factors for IATs in pattern (last is 1 to keep same distance between patterns)
        # Draws factors for IATs between 0.1 and 0.9 by default
        pattern_distance = [ round(random.uniform(pattern_iat_lower,pattern_iat_upper),ROUND_DIGITS) for i in range(0,packets_per_pattern - 1) ] + [1]

        # Stream is periodic after the second full ocurrence of a pattern
        second_pattern_end = (packets_per_pattern) * 2 + 1

        # Change labels after second full ocurrence to periodic
        labels[second_pattern_end:] = 1
    else:
        # Initialize labels as 0 = non-periodic
        labels = np.zeros((count))
    

    if is_periodic:
        # Loop over all iats
        # Apply pattern_distance iteratively to generated IATs
        for i in range(0,iats.shape[0]):

            # Get index for patter ndistance
            pattern_index = i % packets_per_pattern 
            # Multiplay IAT with patter nfactor
            iats[i] = iats[i] * pattern_distance[pattern_index]

    return iats, labels


def sample_near_periodic_stream(period, max_stddev, count):
    """ Generates a near periodic stream based on passed parameters.
    Near periodic is achieved by increasing a single IAT such that the normalized standard deviation is still below the given value.

    Args:
        period (float): Target period for stream_
        max_stddev (float): Maximum normalized stddev over entire stream
        count (int): Number of IATs to generate for stream

    Returns:
        list,list: IATs and stream labels
    """

    # Select index of IAT to increase for near-periodicity
    index = np.random.choice(range(0, count-1))

    # Generate count iats = period
    iats = np.asarray([period for i in range(0, count)])
    # Initialize labels with count elements
    labels = np.ones((count))

    # Holds last known values
    last_val = 0
    last_i = 0

    # step size for first search
    step_size = 1000

    # Two-step search for maximum possible IAT (at index) that still conforms to the condition: normalized standard deviation of stream <= max_stddev
    # First step: step_size is used until condition fails
    # Second step: Increase last possible value by one until condition fails
    # -> Find the max possible value that still conforms
    # TODO: optimize search using library

    # First iteration with step_size
    for i in range(0, int(10**6), step_size):

        # Increse iat
        iats[index] = period + (i*PERIOD_FACTOR)
        # new
        iats[index+1] = period - (i*PERIOD_FACTOR)

        # Calcultae normalized standard deviation
        stdev = statistics.stdev(iats)
        nstdev = stdev/period

        # Check condition
        if nstdev >= max_stddev:
            # Save last val and break search if condition fails
            iats[index] = last_val
            break

        # Update last conforming values
        last_val = iats[index]
        last_i = i

    # Second iteration: start with last conforming value from first search
    for i in range(0, step_size):

        # increase IAT
        iats[index] = period + ((last_i + i)*PERIOD_FACTOR)
        iats[index+1] = period - ((last_i + i)*PERIOD_FACTOR)

        # Calculate normalized standard deviation
        stdev = statistics.stdev(iats)
        nstdev = stdev/period

        # Check condition
        if nstdev >= max_stddev:
            break

        # Store last conforming value
        last_val = iats[index]

    # Set iat to last conforming value
    iats[index] = last_val

    # Update labels: after the outlying IAT, stream is not considered periodic anymore
    labels[int(index):] = 0

    return iats, labels

def load_dataset(path,types=None,dataset="test"):
    data = None

    with open(path, 'rb') as handle:
        data = pickle.load(handle)

    iat_features = []
    labels = []
    lengths = []
    coeffs = []

    if types is None:
        for key, val in data[dataset].items():
                iat_features.extend(val["samples"])
                labels.extend(val["labels"])
                lengths.extend(val["pattern_length"])
                coeffs.extend(val["coeffs"])
    else:
        for key, val in data[dataset].items():
            if val["type"] in types:
                iat_features.extend(val["samples"])
                labels.extend(val["labels"])
                lengths.extend(val["pattern_length"])
                coeffs.extend(val["coeffs"])


    return iat_features, labels, lengths, coeffs

