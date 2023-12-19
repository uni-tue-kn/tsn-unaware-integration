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

#ifndef SCIP_LINKLAYER_MIRRORINGRELAYINTERFACESELECTOR_H_
#define SCIP_LINKLAYER_MIRRORINGRELAYINTERFACESELECTOR_H_

#include <omnetpp.h>
#include "inet/linklayer/ethernet/common/RelayInterfaceSelector.h"


using namespace omnetpp;
using namespace inet;

class MirroringRelayInterfaceSelector : public RelayInterfaceSelector {
public:
    MirroringRelayInterfaceSelector();
    virtual ~MirroringRelayInterfaceSelector();
protected:
    virtual void initialize(int stage) override;
    virtual int numInitStages() const;
private:
    void sendPacket(Packet *packet, const MacAddress& destinationAddress, NetworkInterface *outgoingInterface) override;
    void broadcastPacket(Packet *outgoingPacket, const MacAddress& destinationAddress, NetworkInterface *incomingInterface) override;
    NetworkInterface* mirroredInterface;
    NetworkInterface* mirroringInterface;
};

#endif /* SCIP_LINKLAYER_MIRRORINGRELAYINTERFACESELECTOR_H_ */
