package scip.node;

import inet.node.tsn.TsnSwitch;
import inet.protocolelement.redundancy.StreamCoderLayer;
import inet.linklayer.ethernet.EthernetInterface;


import scip.core.SCIPInterface;

import scip.linklayer.ExtendedStreamEncoder;

module SCIPSwitch extends TsnSwitch
{
    
    parameters:
        // bridging.typename = "TSNUnawareBridgingLayer";
        // bridging.streamCoder.decoder.typename = "ExtendedStreamDecoder";
        bridging.streamCoder.encoder.typename = "ExtendedStreamEncoder";
        //ethernet.typename = "EthernetEncapsulation";
    gates:
       input scipInterface;
    submodules:
       scipInterfaceModule: SCIPInterface {
           @display("p=100,42;is=s");
       }
    
	connections: 
	    scipInterface --> scipInterfaceModule.confMessageIn;
}
