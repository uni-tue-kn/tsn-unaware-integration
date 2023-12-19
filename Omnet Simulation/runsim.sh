#!/bin/bash
INET=/root/inet4.4
SCIP=/root/models/scip
SIM=$SCIP/simulations/TSNUnawareOnly/
TARGET_SIM=$SIM/3_overloaded_network_with_SCIP.ini

# build scip library
cd $SCIP && make

# run simulation
$SCIP/scip -m -n "$SCIP/src:$SCIP/simulations/TSNUnawareOnly:$INET/examples:$INET/showcases:$INET/src" -l $INET/src/INET $TARGET_SIM

# export results to csv file
opp_scavetool x $SIM/results/*.vec -o $SCIP/../result.csv