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

#include "PromiscuousIpv4.h"

Define_Module(PromiscuousIpv4);

PromiscuousIpv4::PromiscuousIpv4() {
    // TODO Auto-generated constructor stub

}

PromiscuousIpv4::~PromiscuousIpv4() {
    // TODO Auto-generated destructor stub
}

void PromiscuousIpv4::preroutingFinish(Packet *packet) {
    // This is called after the initial packet parsing, checking done by Ipv4
    // Here, we just forward the packet upwards without any further handling.
    // Please note, that this only works since the SCIP Stream Manager is listening for all protocols on the next
    // Message dispatcher.
    Ipv4::reassembleAndDeliver(packet);
}
