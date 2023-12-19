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

package scip.applications;

import scip.applications.base.IStreamLifecycleManager;

simple StreamLifecycleManager like IStreamLifecycleManager {
    parameters:
        string streamDatabaseModule = default("^.streamDB");
        string streamClassifierModule = default("^.classifier");
        string cucModule = default("^.cuc");
        string switchConfiguratorModule = default("^.switchConfigurator");
        string interfaceTableModule = default("^.interfaceTable");
        int packetThreshold = default(10);
        
        double activeStreamTimeout = default(5);
        double pendingStreamTimeout = default(15);
        
        
        // While the SCIPs job is to dynamically detect streams, 
        // this implementation does not cover an extensive network discovery and configuration portocol.
        // The SCIP needs to know which switch adds the VLAN tag and which one removes it.
        // Structure of entry:
        // {
        //   srcIP:,
        //   dstIP:,
        //   srcPort:,       -> StreamIDTuple
        //   dstPort:,
        //   l4Proto:,
        //   uniqueID: TSN unique stream ID,
        //   name: unique stream name as string 
        // }
        object streams = default([]);
        
        @display("i=block/cogwheel");
    gates:
        input packetIn;
        output lowerLayerOut;
}