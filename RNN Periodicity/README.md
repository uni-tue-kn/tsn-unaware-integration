# RNN Periodicity Detection

## Files

**train.py** Script to train an RNN model based on the data provided in `data/data.pickle`

**eval.py** Script to evaluate an RNN model on the data provided in `data/data.pickle`

**settings.py** File containing parameters for the training and evaluation

## Training RNN

The resulting RNN is stored under `data/best.keras`.

## Eval RNN

The resulting eval is stored under `data/NN_eval.json`.
The first JSON key equals the threshold used.
The following keys `accuracy`, `recall`, `precision` and `f1_score` select on of the metrics from the evaluation.
The selected value is a list of the collected metrics after i samples.
