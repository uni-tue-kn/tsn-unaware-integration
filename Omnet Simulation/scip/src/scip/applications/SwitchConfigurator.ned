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

import scip.applications.base.ISwitchConfigurator;

//
// TODO auto-generated type
//
simple SwitchConfigurator like ISwitchConfigurator
{
    parameters:
        @namespace(scip);
        @display("i=block/departure");
        int numSwitches = default(0);

        // While the SCIPs job is to dynamically detect streams, 
        // this implementation does not cover an extensive network discovery and configuration portocol.
        // The SCIP needs to know which switch adds the VLAN tag and which one removes it.
        // Structure of entry:
        // {
        //   uniqueID: uniqueID,
        //   switches: [1,0,2] -> array with index = switch id
        // }             1: add tag, 2 remove tag, 0 do nothing
        //               Should contain numSwitches number of entries
        object streams = default([]);

    gates:
        output switches[numSwitches];
}
