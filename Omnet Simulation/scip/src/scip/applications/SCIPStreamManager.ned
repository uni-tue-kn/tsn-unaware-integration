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
import scip.applications.base.IStreamDatabase;
import scip.applications.base.IStreamClassifier;
import scip.applications.base.ISwitchConfigurator;
import scip.applications.base.ICUC;

//
// TODO auto-generated type
//
module SCIPStreamManager
{
    parameters:
        int numSwitches = default(0);
        @display("bgb=290,150");
    gates:
        //inout cncInterfaceg;
        output toSwitches[numSwitches];
        input packetIn;
        output lowerLayerOut;
        inout cnc;
    submodules:
        lifecycleManager: <default("StreamLifecycleManager")> like IStreamLifecycleManager {
            @display("p=145,75");
        }
        cncInterface: <default("CUC")> like ICUC {
            @display("p=250,110;is=s");
        }
        streamDB: <default("StreamDatabase")> like IStreamDatabase {
            @display("p=40,40;is=s");
        }
        classifier: <default("StreamClassifier")> like IStreamClassifier {
            @display("p=40,110;is=s");
        }
        switchConfigurator: <default("SwitchConfigurator")> like ISwitchConfigurator {
            @display("p=250,40;is=s");
            numSwitches = parent.numSwitches;
        }
    connections:
        // Connection to CNC
        //cncInterface.cnc <--> cncInterfaceg;
        // Connections to switches for configuration
        for i=0..(numSwitches-1) {
            switchConfigurator.switches[i] --> toSwitches[i];
        }
        // Connections to lifecycleManager for receiving and sending packets
        packetIn --> lifecycleManager.packetIn;
        lowerLayerOut <-- lifecycleManager.lowerLayerOut;
        
        cncInterface.cnc <--> cnc;


}
