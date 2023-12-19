#!/bin/bash

# Get inet package
#git clone git@github.com:inet-framework/inet.git inet

# Usign docker image omnetpp:u22.04-6.0 (Ubuntu LTS 22.04, Omnet++ 6.0)
# Reference: https://omnetpp.org/articles/2019/07/04/omnetpp-docker.html (14.12.2023)
docker run --rm -it -v "$(pwd):/root/models" -u "root:root" omnetpp/inet:o6.0-4.4.1

