

namespace scip;

// TODO: EndStationInterfaces Group contains a MAC Address as well
// Messages built as defined in Ieee 802.1Qcc

//
// Represents a stream reservation message
//
message TalkerGroupMsg {
    // Stream ID
    uint64_t macAdress;
    uint16_t uniqueID;
   	// Stream Rank
    uint8_t streamRank;
    // EndStationInterfaces
    uint64_t sendAdress;
    string interfaceName;
    // DataFrameSpecification
    uint32_t srcAddr;
    uint32_t dstAddr;
    unsigned short srcPort;
    unsigned short dstPort;
    uint8_t l4Proto;
    // TrafficSpecification
    float interval;
    uint16_t maxFramesPerInterval;
    uint16_t maxFrameSize;
    uint8_t transmissionSelection;
    // UserToNetworkRequirements
    uint8_t numSeamlessTrees;
    uint32_t maxLatency;
}

// Omits UserToNetworkRequirements and InterfaceCapabilities for simplicity
message ListenerGroupMsg {
    // Stream ID
    uint64_t macAdress;
    uint16_t uniqueID;
    // EndStationInterfaces
    string interfaceName;
    uint64_t recvAdress;
}

// TODO: Missing InterfaceConfiguration and FailedIntefaces
// For simplicity, passes streamRank as single parameter
// Response group from CNC
message StatusGroupMsg {
    // Stream ID
    uint64_t macAdress;
    uint16_t uniqueID;
    // Status Info
    uint8_t talkerStatus;
    uint8_t listenerStatus;
    uint8_t failureCode;
    // Accumulated Latency
    uint32_t accumulatedLatency;
    // Should be InterfaceConfiguration but is only PCP and VLAN ID for simplicity
    uint8_t pcp;
    uint16_t vlanID;
}
