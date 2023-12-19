/*
 * StreamLifecycleManager.h
 *
 *  Created on: May 22, 2022
 *      Author: moritz
 */

#include "StreamLifecycleManager.h"

#include "inet/networklayer/ipv4/Ipv4Header_m.h"
#include "inet/transportlayer/udp/UdpHeader_m.h"
#include "inet/common/IProtocolRegistrationListener.h"

#include "inet/common/ModuleAccess.h"

#include "inet/networklayer/ipv4/Ipv4Header_m.h"
#include "inet/linklayer/ethernet/common/EthernetMacHeader_m.h"
#include "inet/transportlayer/udp/UdpHeader_m.h"
#include "inet/transportlayer/tcp_common/TcpHeader_m.h"

#include "scip/core/TSNStream.h"

#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/common/ProtocolTag_m.h"

#include "inet/networklayer/common/NetworkInterface.h"
#include "inet/linklayer/common/InterfaceTag_m.h"

//#include "inet/common/LayeredProtocolBase.h"
//#include "inet/common/ModuleAccess.h"

Define_Module(StreamLifecycleManager);

void StreamLifecycleManager::initialize() {
    // get used module references from parameters
    streamDB = getModuleFromPar<IStreamDatabase>(par("streamDatabaseModule"),
            this);
    classifier = getModuleFromPar<IStreamClassifier>(
            par("streamClassifierModule"), this);
    cuc = getModuleFromPar<ICUC>(par("cucModule"), this);
    switchConfigurator = getModuleFromPar<ISwitchConfigurator>(
            par("switchConfiguratorModule"), this);
    interfaceTable = getModuleFromPar<InterfaceTable>(
            par("interfaceTableModule"), this);

    // get other parameters
    classificationThreshold = par("packetThreshold");

    activeStreamTimeout = par("activeStreamTimeout");
    pendingStreamTimeout = par("pendingStreamTimeout");

    // input packetIn;
    //output lowerLayerOut;

    // Ensure that all packets are delivered from the network layer to this module
    registerProtocol(Protocol::udp, gate("lowerLayerOut"), gate("packetIn"));
    registerProtocol(Protocol::tcp, gate("lowerLayerOut"), gate("packetIn"));

    parseStaticConfig();
}

void StreamLifecycleManager::parseStaticConfig() {
    cValueArray *streamPar = check_and_cast<cValueArray*>(
            par("streams").objectValue());

    for (int i = 0; i < streamPar->size(); i++) {

        cValueMap *element = check_and_cast<cValueMap*>(
                streamPar->get(i).objectValue());

        StreamIDTuple newIdTuple = { new Ipv4Address(
                element->get("srcIP").stringValue()), new Ipv4Address(
                element->get("dstIP").stringValue()),
                (unsigned short) element->get("srcPort").intValue(),
                (unsigned short) element->get("dstPort").intValue(),
                static_cast<IpProtocolId>(element->get("l4Proto").intValue()),

        };

        StaticStreamConfig newStaticConf = { (unsigned short) element->get(
                "uniqueID").intValue(), element->get("name").str() };

        // Create new entry in HashMap
        std::pair<StreamIDTuple, StaticStreamConfig> newPair(newIdTuple,
                newStaticConf);

        staticConfig.insert(newPair);

        // Free memory
        //delete (newIdTuple.srcAddr);
        //delete (newIdTuple.dstAddr);
    }
}

void StreamLifecycleManager::handleMessage(cMessage *msg) {
    // Functionality:
    // 1. extract stream ID from packet
    // 2. Perform lookup in database
    // If :
    // - TODO: Stream is blacklisted: stop handling
    // - Stream is new, call handleNewStream
    // - Stream is known, call handleKnownStream

    // Check if stream is a timeout message
    StreamTimeoutMsg *timeout = dynamic_cast<StreamTimeoutMsg*>(msg);
    if (timeout != nullptr) {
        handleStreamTimeout(timeout->getUniqueID());
        delete (msg);
        return;
    }

    // Cast Omnet++ message to INET packet
    Packet *packet = dynamic_cast<Packet*>(msg);

    // Stop processing if not a packet from here on
    if (packet == nullptr) {
        return;
    }

    packet->trimFront();

    // At this point, L2 and L3 headers have already been parsed and converted to Tags
    // Get L3 Information via L3AddressInd Tag
    // Get L4 Protocol from PacketProtocolTag
    // Get L4 Information by parsing UDP/TCP header based on protocol tag
    // TODO: add IPv6 suppport?
    // TODO: better error handling if some information cannot be extarcted

    // L3 Information
    const Ptr<const L3AddressInd> l3Tag = packet->findTag<L3AddressInd>();

    // Stop processing if not found
    if (l3Tag == nullptr) {
        delete msg;
        return;
    }

    Ipv4Address srcAddr = l3Tag->getSrcAddress().toIpv4();
    Ipv4Address destAddr = l3Tag->getDestAddress().toIpv4();

    // L4 Protocol
    const Ptr<const PacketProtocolTag> protocolTag = packet->findTag<
            PacketProtocolTag>();

    // Stop processing if not found
    if (protocolTag == nullptr) {
        delete msg;
        return;
    }
    const Protocol *l4Proto = protocolTag->getProtocol();

    // L4 Information
    unsigned short srcPort;
    unsigned short destPort;
    unsigned short l4ProtoId;

    if (*l4Proto == Protocol::udp) {
        // Fetch header from packet
        const Ptr<const UdpHeader> hUdp = packet->peekAtFront<UdpHeader>();

        // Get ports
        srcPort = hUdp->getSrcPort();
        destPort = hUdp->getDestPort();
        l4ProtoId = 17;
    }
    if (*l4Proto == Protocol::tcp) {
        // Fetch header from packet
        const Ptr<const tcp::TcpHeader> hTcp = packet->peekAtFront<
                tcp::TcpHeader>();

        // Get ports
        srcPort = hTcp->getSrcPort();
        destPort = hTcp->getDestPort();
        l4ProtoId = 6;

    }

    // Check if the L4 Header could be parsed and read
    // If not, discard this message and stop processing
    if (srcPort == 0 || destPort == 0) {
        delete msg;
        return;
    }

    // Build stream identifier struct
    StreamIDTuple stream = { &srcAddr, &destAddr, srcPort, destPort,
            static_cast<IpProtocolId>(l4ProtoId) };

    // Check if stream known through lookup
    StreamDbEntry *entry = streamDB->lookupStream(&stream);

    if (entry != nullptr) {
        // Stream already known
        handleKnownStream(stream, packet, entry);
    } else {
        // Stream not known, new stream
        handleNewStream(stream, packet);
    }

    delete(msg);
} // function handleMessage

void StreamLifecycleManager::handleStreamTimeout(uint16_t id) {
    // Get relevant entry
    StreamDbEntry *entry = streamDB->lookupStreamUniqueID(id);

    //TODO: further handling:
    // notify cnc
    // revoke switch configuration

    // Set timeouted state
    entry->state = stopped;

    // TODO: this may hapen while stream is announced to cnc,
    //  or classified. Ensure that no weird states are reached.

}

void StreamLifecycleManager::handleKnownStream(StreamIDTuple stream,
        Packet *packet, StreamDbEntry *entry) {

    // Increment packet counter
    entry->packetCount = entry->packetCount + 1;

    // Get interface for pcap writer
    const Ptr<const InterfaceInd> interfaceInd =
            packet->findTag<InterfaceInd>();
    NetworkInterface *incomingInterface;

    // TODO: this could be stored as attributed, prevent lookup for each new packet
    if (interfaceInd != nullptr) {
        // get reference to incoming interface
        incomingInterface = interfaceTable->getInterfaceById(
                interfaceInd->getInterfaceId());
    } else {
        // No incoming interface, discard
        // Should not be reached
        return;
    }

    if (entry->state == pending) {
        // Store packet
        entry->pcap->writePacket(simTime(), packet, DIRECTION_INBOUND,
                        incomingInterface, LINKTYPE_ETHERNET);
        // Check if threshold for classification reached
        if (entry->packetCount >= classificationThreshold) {
            // Update state
            entry->state = awaiting_classification;

            //Signal to stream classifier
            classifier->classifyStream(&stream, entry);

            // TODO: this should be triggered via callback by the classifier
            cuc->registerStream(&stream, entry->streamInfo);

        }

        // Update Stream Timeout:
        // - cancel old event
        // - schedule new timeout event
        cancelEvent(entry->timeoutMsg);
        // Schedule new timeout event for this stream
        StreamTimeoutMsg *timeout = new StreamTimeoutMsg();
        timeout->setUniqueID(entry->streamInfo->getUniqueID());
        // Use timeout for pending stream
        scheduleAt(simTime() + pendingStreamTimeout, timeout);
        // Store reference in stream entry
        entry->timeoutMsg = timeout;

    }

    if (entry->state == established) {
        // Update Stream Timeout:
        // - cancel old event
        // - schedule new timeout event
        cancelEvent(entry->timeoutMsg);
        // Schedule new timeout event for this stream
        StreamTimeoutMsg *timeout = new StreamTimeoutMsg();
        timeout->setUniqueID(entry->streamInfo->getUniqueID());
        // use timeout for active stream
        scheduleAt(simTime() + activeStreamTimeout, timeout);
        // Store reference in stream entry
        entry->timeoutMsg = timeout;
    }

}

void StreamLifecycleManager::handleNewStream(StreamIDTuple stream,
        Packet *packet) {
    streamDB->createStream(stream);

    StreamDbEntry *entry = streamDB->lookupStream(&stream);

    // Get stream unique ID and name from config
    // Perform lookup on unordered map
    std::unordered_map<StreamIDTuple, StaticStreamConfig>::iterator configEntry =
            staticConfig.find(stream);

    // Check if lookup did return a value
    if (configEntry == staticConfig.end()) {
        EV_ERROR
                        << "Did not find a configuration entry for stream. Skipping handling!"
                        << std::endl;
        return;
    } else {
        // Set values from static configuration
        entry->streamInfo->setUniqueID(configEntry->second.uniqueID);
        entry->name = configEntry->second.name;
    }

    StreamIDTuple streamInfo = {
            new Ipv4Address(*stream.srcAddr),
            new Ipv4Address(*stream.dstAddr),
            stream.srcPort,
            stream.dstPort,
            stream.l4Proto
        };

    // Set stream dataFrameSpecification
    entry->streamInfo->setDataFrameSpecification(streamInfo);

    // Let entry extract other required information from the packet
    entry->streamInfo->parsePacket(packet);

    // Get interface for pcap writer
    const Ptr<const InterfaceInd> interfaceInd =
            packet->findTag<InterfaceInd>();


    NetworkInterface* incomingInterface;

    if (interfaceInd != nullptr) {
        // get reference to incoming interface
        incomingInterface = interfaceTable->getInterfaceById(
                interfaceInd->getInterfaceId());
    } else {
        // No incoming interface, discard
        // Should not be reached
        return;
    }

    // Store packet
    entry->pcap->writePacket(simTime(), packet, DIRECTION_INBOUND,
            incomingInterface, LINKTYPE_ETHERNET);

    // Schedule timeout event for this stream
    StreamTimeoutMsg *timeout = new StreamTimeoutMsg();
    timeout->setUniqueID(entry->streamInfo->getUniqueID());
    scheduleAt(simTime() + pendingStreamTimeout, timeout);
    // Store reference in stream entry
    entry->timeoutMsg = timeout;

}

void StreamLifecycleManager::cucCallback(StatusGroupMsg *statusGroup) {
    Enter_Method("cucCallback()");

    StreamDbEntry *entry = streamDB->lookupStreamUniqueID(
            statusGroup->getUniqueID());

    if (entry != nullptr) {

        // Pass data from status group to stream Info class
        entry->streamInfo->parseStatusGroup(statusGroup);

        // Get stream unique ID and name from config
        // Perform lookup on unordered map
        std::unordered_map<StreamIDTuple, StaticStreamConfig>::iterator configEntry =
                staticConfig.find(*entry->streamInfo->getStreamIDTuple());

        // Check if lookup did return a value
        if (configEntry == staticConfig.end()) {
            // TODO: error handling
            return;
        } else {
            StaticStreamConfig *config = &configEntry->second;

            // Signal switch configurator to apply config to switches
            switchConfigurator->writeConfig(
                    entry->streamInfo->getStreamIDTuple(), entry->streamInfo->getMapping(),
                    config->uniqueID, config->name);
        }

    }
}

