//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package scip.node;

import inet.node.base.NetworkLayerNodeBase;

import scip.applications.SCIPStreamManager;

import inet.linklayer.ethernet.EthernetInterface;
import inet.networklayer.common.InterfaceTable;
import inet.networklayer.ipv4.Ipv4RoutingTable;

import scip.applications.base.IStreamLifecycleManager;
import scip.applications.base.IStreamDatabase;
import scip.applications.base.IStreamClassifier;
import scip.applications.base.ISwitchConfigurator;
import scip.applications.base.ICUC;

import inet.linklayer.ethernet.basic.EthernetEncapsulation;

import inet.node.base.TransportLayerNodeBase;
import inet.common.MessageDispatcher;


// We cannot use the inet StandardHost Stack like inet/node/base/ApplicationLayerNodeBase as of now
// While it would be nice to leave header parsing to those modules, they do not support a promiscuous mode like the ethernet layer.
// The solution would be to just implement a promiscuous Transport layer module that just forwards everything to the application layer
module SCIP extends TransportLayerNodeBase
{
    parameters:
        @networkNode;
        int numSwitches = default(0);
        **.interfaceTableModule = default(absPath(".interfaceTable"));
        *.*.promiscuous = true;
        hasUdp = false;
        hasTcp = false;
        hasSctp = false;
        hasIpv4 = true;
        // Use cutsom Ipv4 module, that also forwards packets with a different destination IP address
        ipv4.ip.typename = "PromiscuousIpv4";

        ieee8021q.typename = default("Ieee8021qProtocol");
        llc.typename = default("Ieee8022Llc");

        @display("bgb=1323.344,1173.788");
    gates:
        output switches[numSwitches];
        inout cnc;
    submodules:
        lifecycleManager: <default("StreamLifecycleManager")> like IStreamLifecycleManager {
            @display("p=748.572,58.850002");
        }
        cuc: <default("CUC")> like ICUC {
            @display("is=s;p=124.63,824.82404");
        }
        streamDB: <default("StreamDatabase")> like IStreamDatabase {
            @display("is=s;p=124.63,747.78");
        }
        classifier: <default("DummyStreamClassifier")> like IStreamClassifier {
            @display("is=s;p=124.63,974.38");
        }
        switchConfigurator: <default("SwitchConfigurator")> like ISwitchConfigurator {
            @display("is=s;p=124.63,899.602");
            numSwitches = parent.numSwitches;
        }

    connections:
        lifecycleManager.packetIn <-- tn.out++;
        lifecycleManager.lowerLayerOut --> tn.in++;

        cuc.cnc <--> cnc;

        for i=0..(numSwitches-1) {
            switchConfigurator.switches[i] --> switches[i];
        }


}
