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

package scip.linklayer;

import inet.protocolelement.redundancy.StreamEncoder;


// This class extends the stream encoder to allow it to remove the VLAN tag.
// Each entry in the 'mapping' parameter can have a 'removeVlanTag' key.
// If it exists and is set to true, the Encoder will remove the VLAN Omnet++ Tags and cause the packet
// to leave the switch without a VLAN tag.

simple ExtendedStreamEncoder extends StreamEncoder
{
    parameters:
    	@class(ExtendedStreamEncoder);
    	string fcsMode @enum("disabled","declared","computed") = default("declared");
}