# Concept Evaluation via Omnet++ Simulation

## Running the Simulation

### In Docker
Start the docker container and open an interactive shell
> ./run.sh

Start the simulation inside the docker container
> /root/models/runsim.sh

Unfortunately, there is currently no docker container for inet4.4 that supports a GUI.

You can change 'runsim.sh' to choose another simulation.

### In Omnetpp 

The library was tested for:
- Omnet++ 6.0.2 https://github.com/omnetpp/omnetpp/releases/tag/omnetpp-6.0.2
- INET 4.4.1 https://github.com/inet-framework/inet/releases/tag/v4.4.1

If you want to run the simulation in Omnet directly, install the INET framework and the SCIP library in the same workspace.

Then run the simulations under `scip/simulations`.


## Plotting the Delay

Execute the `plot_results.py` script to generate the figure.
The script expects a `result.csv` file generated with `opp_scavetool` in the same directory.
If you change the simulations `.ini` file, the script has to be adjusted as well.

## Other

The Rhebo Industrial Protector interface has been removed from the simulation.