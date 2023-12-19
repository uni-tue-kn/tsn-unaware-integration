namespace scip;
message AddConfigurationMsg {
    uint8_t switchID;
    string stream;
    bool removeVlanTag = false;
	uint32_t srcAddr;
    uint32_t dstAddr;
    unsigned short srcPort;
    unsigned short dstPort;
    uint8_t l4Proto;
    uint16_t vlanID;
    uint8_t pcp;
    bool de = false;
}

message RemoveConfigurationMsg {
    string stream;
}