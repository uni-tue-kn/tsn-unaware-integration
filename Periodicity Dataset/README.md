# Periodicity Dataset

The scripts in this folder can be used to generate the dataset for the training and evaluation of the RNN and traffic description algorithm.

## Files

**settings.py** contains the dataset generation parameters

**lib.py** contains functions used to generate the dataset

**main.py** can be executed to generate the dataset

## Dataset Generation

Execute `main.py` to start the generation process. 
The generated dataset is stored in the folder `data/`.

## Dataset Format

The streams are stored in the `pickle` file format, the data is organized in the `JSON` format.

```
{
    "test": {
        "periodic": {
            "type": 0,
            "samples": [ ... ],
            "lables": [ ... ],
            "pattern_length": [ ... ],
            "coeffs": [ ... ]
        },
        "nonperiodic": {
            "type": 1,
            ...
        },
        "pattern": {
            "type": 2,
            ...
        },
        "near": {
            "type": 3,
            ...
        }
    },
    "train": {
        ...
    }
}
```

Here, the first key determines whether the test or train dataset is used.
The second keys select on of the four stream classes.
For each stream class, the samples, labels, used pattern length for generation and used coefficient of variation.
To select all values for the same stream, use the same index on all lists.
E.g., samples[0] returns the IATs for the first stream of that class, and labels[0] the associated labels.
pattern_length[0] and coeffs[0] return the parameters used for the generation.

## Reproducibility

Seeds for RNGs are set in settings.py to ensure reproducibility.