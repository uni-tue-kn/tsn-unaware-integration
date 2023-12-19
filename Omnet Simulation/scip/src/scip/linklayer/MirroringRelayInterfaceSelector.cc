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

#include "MirroringRelayInterfaceSelector.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/linklayer/ethernet/contract/IMacForwardingTable.h"

#include "scip/linklayer/IsBroadcastTag_m.h"
using namespace scip;

Define_Module(MirroringRelayInterfaceSelector);

int MirroringRelayInterfaceSelector::numInitStages() const {
    return 3;
}

void MirroringRelayInterfaceSelector::initialize(int stage) {
    if (stage == 0) {
        RelayInterfaceSelector::initialize(stage);
    }

    if (stage == 2) {

        std::string mirroredInterfaceName = par("mirroredInterface");
        std::string mirroringInterfaceName = par("mirroringInterface");

        // Get interface pointer references by name
        // Not that many interfaces, no break needed
        for (int i = 0; i < interfaceTable->getNumInterfaces(); i++) {
            NetworkInterface *interface = interfaceTable->getInterface(i);
            if (interface->getInterfaceName() == mirroringInterfaceName) {
                this->mirroringInterface = interface;
            }
            if (interface->getInterfaceName() == mirroredInterfaceName) {
                this->mirroredInterface = interface;
            }

        }
    }
}

MirroringRelayInterfaceSelector::MirroringRelayInterfaceSelector() {
    // TODO Auto-generated constructor stub
}

MirroringRelayInterfaceSelector::~MirroringRelayInterfaceSelector() {
    // TODO Auto-generated destructor stub
}

void MirroringRelayInterfaceSelector::broadcastPacket(Packet *outgoingPacket,
        const MacAddress &destinationAddress,
        NetworkInterface *incomingInterface) {
    // Add tag to signal to not mirror it!
    // Otherwise, the packet would be copied for each interface and sent over the mirror port
    outgoingPacket->addTagIfAbsent<IsBroadcastTag>();

    // Call normal broadcast handling
    RelayInterfaceSelector::broadcastPacket(outgoingPacket, destinationAddress,
            incomingInterface);
}

void MirroringRelayInterfaceSelector::sendPacket(Packet *packet,
        const MacAddress &destinationAddress,
        NetworkInterface *outgoingInterface) {

    // sendPacket is called by the parent class after finding the outgoing interface from the lookup table
    // This implements the mirroring functionality by duplicating the packet if the unicast destination interface matches
    // the configured mirroring source interface.

    // Get the packets incoming interface
    auto interfaceInd = packet->findTag<InterfaceInd>();
    NetworkInterface *incomingInterface =
            interfaceInd != nullptr ?
                    interfaceTable->getInterfaceById(
                            interfaceInd->getInterfaceId()) :
                    nullptr;

    // Check if this packet is currently in the broadcast processing
    const Ptr<const IsBroadcastTag> isBroadcast =
            packet->findTag<IsBroadcastTag>();
    if (isBroadcast != nullptr) {
        // Remove tag to prevent side effects in further handling
        packet->removeTagIfPresent<IsBroadcastTag>();
    } else {
        // Packet was not broadcast, duplicate
        if (incomingInterface == this->mirroredInterface
                || outgoingInterface == this->mirroredInterface) {
            RelayInterfaceSelector::sendPacket(packet->dup(),
                    destinationAddress, this->mirroringInterface);
        }

    }

    RelayInterfaceSelector::sendPacket(packet, destinationAddress,
            outgoingInterface);

}
