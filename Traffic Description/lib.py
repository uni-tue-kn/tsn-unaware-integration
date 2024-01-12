import sys
from decimal import *

import pickle

ROUND_DIGITS = 12
JITTER_ACCURACY = 0.01

def get_interval_bounds(series):
    res = {}

    for N in range(1,len(series)-1):
        min_interval = 9999999
        
        for i in range(0,len(series)-N):
            start = series[i]
            end = series[i+N]

            c_interval = end - start

            if c_interval < min_interval:
                min_interval = c_interval

        # shorten min interval by expected jitter
        min_interval = min_interval * Decimal(1-JITTER_ACCURACY)

        res[N] = min_interval

    return res


def get_elements_in_interval(series, t, I):
    n = 0
    for arrival in series:
        if t <= arrival and arrival < (t+I):
            n += 1
    return n 

def find_next_event(series, t):
    # Find first entry in series that has a larger timestamp than t
    # which means: find next arrival event after t
    for arrival in series:
        diff = round(arrival -t, 12)
        if diff > 0:
            return arrival
        
    # No next event, return infinity
    return sys.maxsize


def extract_deviation(series):
    # Get interval boudns for given max frames
    bounds = get_interval_bounds(series)
    deviation_res = []

    # Iterate over all possiblities
    for N, I in bounds.items():

        I = round(I, ROUND_DIGITS)

        deviation = 0

        deviation = 0
        t = series[0]
        t_end = series[-1]

        n_cur = get_elements_in_interval(series, t, I) 

        # At the beginning, the next exit event is the current one
        t_E = series[0]
        t_I = find_next_event(series,t+I) - (t+I)

        while t < t_end:

            if t_E < t_I:
                # Next event is exit
                deviation += t_E * (N-n_cur)
                t += t_E
                n_cur -= 1

            elif t_E > t_I:
                # Next event is input
                deviation += t_I * (N-n_cur)
                t += t_I
                n_cur += 1

            else:
                # doesnt matter if t_E or t_I
                deviation += t_E * (N-n_cur)
                t += t_E

            next_in = find_next_event(series,t+I)
            next_out = find_next_event(series,t)

            # Break condition: no other in events
            if next_in == sys.maxsize:
                break
            
            # Get distance from end of interval to next entering arrival time
            t_I = round(next_in - (t+I), ROUND_DIGITS)

            # Get distance from start of interval to next leaving arrival time
            t_E = round(next_out - t, ROUND_DIGITS)

        deviation_res.append((N, I, deviation))

    return deviation_res

    
def iats_to_arrivals(iats):
    arrivals = [round(Decimal(sum(iats[0:j])), ROUND_DIGITS) for j in range(0, len(iats))]
    return arrivals


    
def extract_timing(iats):
    # Convert IATs to absolute arrival times
    arrivals = [round(Decimal(sum(iats[0:j])), ROUND_DIGITS) for j in range(0, len(iats))]
    # Get metrics for cost function
    bounds = get_interval_bounds(arrivals)
    timings = extract_deviation(arrivals)

    n = max(bounds, key=bounds.get)
    

    costs = []
    for N, I in bounds.items():

        # Limit search range to Nmax
        if N > int(n/2):
            break

        reg = arrivals[-1]-I-arrivals[0]
        costs.append(timings[N-1][2]/reg)

    #costs = [timings[i][2] for i in range(0,len(timings))]
    # + 1 since costs[0] is for N = 1
    best_fit = costs.index(min(costs)) + 1

    return best_fit, bounds[best_fit]

def load_dataset(path,types=None,dataset="test"):
    data = None

    with open(path, 'rb') as handle:
        data = pickle.load(handle)


    iat_features = []
    labels = []
    lengths = []
    stddevs = []

    if types is None:
        for key, val in data[dataset].items():
                iat_features.extend(val["samples"])
                labels.extend(val["labels"])
                lengths.extend(val["pattern_length"])
                stddevs.extend(val["stddevs"])
    else:
        for key, val in data[dataset].items():
            if val["type"] in types:
                iat_features.extend(val["samples"])
                labels.extend(val["labels"])
                lengths.extend(val["pattern_length"])
                stddevs.extend(val["stddevs"])


    return iat_features, labels, lengths, stddevs

