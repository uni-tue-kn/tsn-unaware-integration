from lib import *
from tqdm import tqdm
import multiprocessing as mp
import json

import random
import numpy as np

NUM_PROCS = 16

# Set seed for reproduceability
random.seed(1245)
np.random.seed(1245)

def proc_run(iats,lengths,stddevs,start_index,dict):

    for i in tqdm(range(0,len(iats)),"Start index: {}".format(start_index)):

        # TODO
        N,I = extract_timing(iats[i])

        dict[start_index+i] = {
                "iats": iats[i].tolist(),
                "N": N,
                "I": float(I),
                "pattern_length": lengths[i],
                "stddevs": stddevs[i]
            }


def main(num_procs=1):

    num_correct = 0
    num_false = 0

    # 0 - periodic
    # 2- periodic pattern
    iats, _, lengths,stddevs = load_dataset("data.pickle",types=[0,2])
    iats2, _, lengths2,stddevs2 = load_dataset("data.pickle",types=[0,2],dataset="train")

    iats.extend(iats2)
    lengths.extend(lengths2)
    stddevs.extend(stddevs)

    faults = {}

    num_streams = len(iats)

    true_period = []
    predicted_period = []

    res_dict = mp.Manager().dict()

    splits = int(num_streams/num_procs)

    # Start processes
    procs = []
    for j in range(0,num_procs):
        start_index = j*splits
        end_index = ((j+1)*(splits))
        if j == (num_procs-1):
            split_iats = iats[start_index:]
            split_lengths = lengths[start_index:]
            split_stddevs = stddevs[start_index:]
        else:
            split_iats = iats[start_index:end_index]
            split_lengths = lengths[start_index:end_index]
            split_stddevs = stddevs[start_index:end_index]

        

        new_p = mp.Process(target=proc_run,args=(split_iats,split_lengths,split_stddevs,start_index,res_dict))
        new_p.start()

        procs.append(new_p)


    # Wait for all processes to finish
    for p in procs:
        p.join()



    # Calculate results
    results = {
            1: {
                "correct": 0,
                "total": 0            
            },
            2: {
                "correct": 0,
                "total": 0
            },
            3: {
                "correct": 0,
                "total": 0
            },
            4: {
                "correct": 0,
                "total": 0
            }
        }
    i = 0
    for key in res_dict.keys():
        val = res_dict[key]
        #print(val)
        real = int(val["pattern_length"])
        predicted = int(val["N"])

        results[real]["total"] += 1

        if real == predicted:
            results[real]["correct"] += 1
        else:
            faults[i] = {
                "iats": val["iats"],
                "N": predicted,
                "I": val["I"],
                "pattern_length": real,
                "stddev": val["stddevs"]
            }

            #pass
            #print(iats[i])
            print("Mismatch {} guessed: {}".format(real,predicted))
        
        if predicted in results[real]:
            results[real][predicted] += 1
        else:
            results[real][predicted] = 1

        true_period.append(real)
        predicted_period.append(predicted)

        i += 1


    print(results)

    print("Total guessed: {}. Correctly guessed: {}. Incorrectly guessed: {}. Accuracy: {}".format(num_correct+num_false,num_correct, num_false, num_correct/num_streams))
    
    with open("fails.json","w") as outfile:
        outfile.write(json.dumps(faults))

    with open("results.json","w") as outfile:
        outfile.write(json.dumps({
            "periods": true_period,
            "predicted": predicted_period
        }))



if __name__ == "__main__":
    main(num_procs=16)