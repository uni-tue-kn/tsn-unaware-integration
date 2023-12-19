//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

package scip.simulations.TSNUnawareOnly;
@namespace(scip);

import inet.networks.base.TsnNetworkBase;
import inet.node.contract.IEthernetNetworkNode;
import inet.node.ethernet.Eth1G;
import inet.node.ethernet.EthernetHost;

import inet.node.tsn.TsnSwitch;
import inet.node.tsn.TsnDevice;

import inet.node.inet.StandardHost;

import scip.node.SCIPSwitch;
import scip.node.MirroringSCIPSwitch;
import scip.node.SCIP;
import scip.node.CNC;

network TSNUnawareOnly extends TsnNetworkBase
{
    parameters:
        *.eth[*].bitrate = 1Gbps;
        *.eth.bitrate = 1Gbps;
        // Make StandardHosts compatible with TSN Network:
        // inet4.4 TSN devices use modular modules ethernet which work a bit differently from the standard ethernet interfaces.
        // By default, TSN devices/switches always output a 'Signal' instead of an 'EthernetSignal', as done by standard hosts
        //   this would cause an error in the receiving StandardHost interface
        tsnUnaware*.ethernet.typename = "EthernetLayer";
        tsnUnaware*.eth[*].typename = "LayeredEthernetInterface";
        load*.ethernet.typename = "EthernetLayer";
        load*.eth[*].typename = "LayeredEthernetInterface";
        scip.ethernet.typename = "EthernetLayer";
        scip.eth[*].typename = "LayeredEthernetInterface";

    submodules:
        tsnUnawareSource: StandardHost {
            @display("p=300,150");
        }
        loadSource1: StandardHost {
            @display("p=300,255");
        }
        loadSource2: StandardHost {
            @display("p=300,350");
        }
        switch1: MirroringSCIPSwitch {
            @display("p=500,250");
            mirroredPort = "eth0";
            mirroringPort = "eth3";
        }
        switch2: SCIPSwitch {
            @display("p=700,250");
        }
        tsnUnawareSink: StandardHost {
            @display("p=900,150");
        }
        loadSink: StandardHost {
            @display("p=900,350");
        }
        scip: SCIP {
            @display("p=592,150");
        }
        cnc: CNC {
        // SCIP eth interface has to be promiscuous
            @display("p=700,150");
        }
    connections:

        // Tsn Unaware Clients
        tsnUnawareSource.ethg++ <--> Eth1G <--> switch1.ethg++;
        switch2.ethg++ <--> Eth1G <--> tsnUnawareSink.ethg++;

        // Load Generation Clients
        loadSource1.ethg++ <--> Eth1G <--> switch1.ethg++;
        loadSource2.ethg++ <--> Eth1G <--> switch1.ethg++;
        switch2.ethg++ <--> Eth1G <--> loadSink.ethg++;

        // SCIP
        scip.ethg++ <--> Eth1G <--> switch1.ethg++;
        //scip.ethg++ <--> Eth1G <--> switch1.ethg++;
        scip.switches++ --> switch1.scipInterface;
        scip.switches++ --> switch2.scipInterface;

        // Other Network Links
        switch1.ethg++ <--> Eth1G <--> switch2.ethg++;

        cnc.scip <--> scip.cnc;
}

