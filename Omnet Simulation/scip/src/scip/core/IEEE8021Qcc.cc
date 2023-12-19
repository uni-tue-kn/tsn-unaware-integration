//cZ5
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

#include "IEEE8021Qcc.h"
#include "inet/linklayer/common/MacAddressTag_m.h"
#include "inet/linklayer/common/MacAddress_m.h"

IEEE8021QccStreamInfo::IEEE8021QccStreamInfo() {
    // TODO Auto-generated constructor stub

}

IEEE8021QccStreamInfo::~IEEE8021QccStreamInfo() {
    // TODO Auto-generated destructor stub
}

void IEEE8021QccStreamInfo::setStreamID(StreamID id) {
    streamID = id;
}
void IEEE8021QccStreamInfo::setStreamRank(uint8_t rank) {
    streamRank = rank;
}
void IEEE8021QccStreamInfo::setTalkerInterfaces(
        EndStationInterfaces interfaces) {
    talkerInterfaces = interfaces;
}
void IEEE8021QccStreamInfo::setListenerInterfaces(
        EndStationInterfaces interfaces) {
    listenerInterfaces = interfaces;
}
void IEEE8021QccStreamInfo::setDataFrameSpecification(StreamIDTuple spec) {
    dataFrameSpecification = spec;
}
void IEEE8021QccStreamInfo::setTrafficSpecification(TrafficSpecification spec) {
    trafficSpecification = spec;
}
void IEEE8021QccStreamInfo::setUserToNetworkRequirements(
        UserToNetworkRequirements reqs) {
    userToNetworkRequirements = reqs;
}
TalkerGroupMsg* IEEE8021QccStreamInfo::generateTalkerGroup(std::string name) {
    TalkerGroupMsg *talkerGroup = new TalkerGroupMsg(name.c_str());

    // Stream ID Group
    talkerGroup->setMacAdress(streamID.macAdress->getInt());
    talkerGroup->setUniqueID(streamID.uniqueID);

    // Stream Rank Group
    talkerGroup->setStreamRank(streamRank);

    // End Station Interfaces group
    //talkerGroup->setSendAdress(talkerInterfaces.macAdress->getInt());
    //talkerGroup->setInterfaceName(talkerInterfaces.interfaceName.c_str());

    // Data Frame Specification Group
    talkerGroup->setSrcAddr(dataFrameSpecification.srcAddr->getInt());
    talkerGroup->setDstAddr(dataFrameSpecification.dstAddr->getInt());
    talkerGroup->setSrcPort(dataFrameSpecification.srcPort);
    talkerGroup->setDstPort(dataFrameSpecification.dstPort);
    talkerGroup->setL4Proto(dataFrameSpecification.l4Proto);

    // Traffic Specification group
    talkerGroup->setInterval(trafficSpecification.interval);
    talkerGroup->setMaxFramesPerInterval(
            trafficSpecification.maxFramesPerInterval);
    talkerGroup->setMaxFrameSize(trafficSpecification.maxFrameSize);
    talkerGroup->setTransmissionSelection(
            trafficSpecification.transmissionSelection);

    // User to Network requirements Group
    talkerGroup->setNumSeamlessTrees(
            userToNetworkRequirements.numSeamlessTrees);
    talkerGroup->setMaxLatency(userToNetworkRequirements.maxLatency);

    return talkerGroup;

}
ListenerGroupMsg* IEEE8021QccStreamInfo::generateListenerGroup(
        std::string name) {

    ListenerGroupMsg *listenerGroup = new ListenerGroupMsg(name.c_str());

    // Stream ID
    listenerGroup->setMacAdress(streamID.macAdress->getInt());
    listenerGroup->setUniqueID(streamID.uniqueID);

    // End Station Interfaces
    //listenerGroup->setInterfaceName(listenerInterfaces.interfaceName.c_str());
    //listenerGroup->setRecvAdress(listenerInterfaces.macAdress->getInt());

    return listenerGroup;
}

void IEEE8021QccStreamInfo::setAccumulatedLatency(uint32_t latency) {
    accumulatedLatency = latency;
}

uint16_t IEEE8021QccStreamInfo::getUniqueID() {
    return streamID.uniqueID;
}

void IEEE8021QccStreamInfo::parseStatusGroup(StatusGroupMsg *statusGroup) {

    accumulatedLatency = statusGroup->getAccumulatedLatency();

    mapping = { statusGroup->getVlanID(), statusGroup->getPcp(), 0 };

    status = { statusGroup->getTalkerStatus(), statusGroup->getListenerStatus(),
            statusGroup->getFailureCode() };
}

StreamIDTuple* IEEE8021QccStreamInfo::getStreamIDTuple() {
    return &dataFrameSpecification;
}

void IEEE8021QccStreamInfo::setUniqueID(uint16_t id) {
    streamID.uniqueID = id;
}

// Parse Stream information from packet headeers
void IEEE8021QccStreamInfo::parsePacket(Packet *packet) {
    // TODO: implement

    // Get Mac Src and Dest
    // Set interface name
    const Ptr<const MacAddressInd> macInd = packet->findTag<MacAddressInd>();

    if (macInd != nullptr) {
        // create stable pointer from packets mac address
        streamID.macAdress = new MacAddress(macInd->getSrcAddress());
    }

}

CBMapping* IEEE8021QccStreamInfo::getMapping() {
    return &mapping;
}

