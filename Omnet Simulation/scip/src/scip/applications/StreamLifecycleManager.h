/*
 * StreamLifecycleManager.h
 *
 *  Created on: May 22, 2022
 *      Author: moritz
 */

#ifndef STREAMLIFECYCLEMANAGER_H
#define STREAMLIFECYCLEMANAGER_H

//#include "inet/linklayer/ethernet/EtherFrame_m.h"
//#include "inet/common/packet/Packet.h"
#include <omnetpp.h>
#include <unordered_map>

#include "base/ICUC.h"

#include "inet/common/packet/Packet.h"
#include "inet/linklayer/common/MacAddress.h"

#include "scip/applications/base/IStreamDatabase.h"
#include "scip/applications/base/IStreamClassifier.h"
#include "scip/applications/base/ISwitchConfigurator.h"

#include "inet/networklayer/common/InterfaceTable.h"
#include "inet/common/ModuleRefByPar.h"

#include "scip/messages/streamReservation_m.h"

#include "scip/messages/streamTimeout_m.h"

using namespace omnetpp;
using namespace inet;
//using namespace nesting;

//namespace scip {

struct StaticStreamConfig {
    uint16_t uniqueID;
    std::string name;
};

class StreamLifecycleManager : public cSimpleModule
{
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage* msg) override;
    void parseStreamConfig();
    // Mapping stream parameters to stream ID
    std::unordered_map<StreamIDTuple, StaticStreamConfig> staticConfig;
    void parseStaticConfig();
private:
    double activeStreamTimeout;
    double pendingStreamTimeout;
    int classificationThreshold;
    // references to other components
    InterfaceTable* interfaceTable;
    IStreamDatabase* streamDB;
    ICUC* cuc;
    IStreamClassifier* classifier;
    ISwitchConfigurator* switchConfigurator;
    void handleNewStream(StreamIDTuple id, Packet* packet);
    void handleKnownStream(StreamIDTuple id, Packet* packet, StreamDbEntry* entry);
    void handleStreamTimeout(uint16_t id);
public:
    void cucCallback(StatusGroupMsg* statusGroup);
};

//} // end namespace scip

#endif
