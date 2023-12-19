package scip.node;


import inet.protocolelement.redundancy.StreamCoderLayer;
import inet.linklayer.ethernet.EthernetInterface;

import scip.core.SCIPInterface;
import scip.linklayer.MirroringRelayInterfaceSelector;
import scip.node.SCIPSwitch;

import inet.linklayer.ethernet.common.RelayInterfaceSelector;


module MirroringSCIPSwitch extends SCIPSwitch
{
 	parameters:
 	    string mirroredPort = default("eth0");
 	    string mirroringPort = default("eth1");
 	    bridging.interfaceRelay.selector.typename = "MirroringRelayInterfaceSelector";
 	    
 	    **.mirroredInterface = mirroredPort;
 	    **.mirroringInterface = mirroringPort;
}
