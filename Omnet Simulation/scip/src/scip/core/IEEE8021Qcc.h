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

#ifndef SCIP_CORE_IEEE8021QCC_H_
#define SCIP_CORE_IEEE8021QCC_H_

#include <omnetpp.h>
#include "scip/messages/streamReservation_m.h"
#include "scip/core/TSNStream.h"
#include "inet/common/packet/Packet.h"


using namespace omnetpp;
using namespace scip;
using namespace inet;

struct StreamID {
    MacAddress* macAdress;
    uint16_t uniqueID;
};

// TODO: implement correctly
struct EndStationInterfaces {
    MacAddress *macAdress;
    std::string interfaceName;
};

struct TrafficSpecification {
    float interval;
    uint16_t maxFramesPerInterval;
    uint16_t maxFrameSize;
    uint8_t transmissionSelection;
};

struct UserToNetworkRequirements {
    uint8_t numSeamlessTrees;
    uint32_t maxLatency;
};

struct StatusInformation {
    uint8_t talkerStatus;
    uint8_t listenerStatus;
    uint8_t failureCode;
};

class IEEE8021QccStreamInfo {
protected:
    StreamID streamID;
    uint8_t streamRank;
    // TODO: EndStationInterfaces can be a List according to 802.1Qcc
    EndStationInterfaces listenerInterfaces;
    EndStationInterfaces talkerInterfaces;
    StreamIDTuple dataFrameSpecification;
    TrafficSpecification trafficSpecification;
    UserToNetworkRequirements userToNetworkRequirements;
    uint32_t accumulatedLatency;
    CBMapping mapping;
    StatusInformation status;
public:
    IEEE8021QccStreamInfo();
    virtual ~IEEE8021QccStreamInfo();
    void setStreamID(StreamID id);
    void setStreamRank(uint8_t rank);
    void setTalkerInterfaces(EndStationInterfaces interfaces);
    void setListenerInterfaces(EndStationInterfaces interfaces);
    void setDataFrameSpecification(StreamIDTuple spec);
    void setTrafficSpecification(TrafficSpecification spec);
    void setUserToNetworkRequirements(UserToNetworkRequirements reqs);
    void setAccumulatedLatency(uint32_t latency);
    void setUniqueID(uint16_t id);
    void parsePacket(Packet* packet);
    TalkerGroupMsg* generateTalkerGroup(std::string name);
    ListenerGroupMsg* generateListenerGroup(std::string name);
    uint16_t getUniqueID();
    void parseStatusGroup(StatusGroupMsg* statusGroup);
    StreamIDTuple* getStreamIDTuple();
    CBMapping* getMapping();
};

#endif /* SCIP_CORE_IEEE8021QCC_H_ */

