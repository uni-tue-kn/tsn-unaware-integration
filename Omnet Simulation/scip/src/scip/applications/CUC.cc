/*
 * CUC.h
 *
 *  Created on: May 22, 2022
 *      Author: moritz
 */

#include "CUC.h"

#include "scip/messages/streamReservation_m.h"
#include "inet/common/ModuleAccess.h"

//namespace scip {

Define_Module(CUC);

void CUC::initialize() {
    streamManager = getModuleFromPar<StreamLifecycleManager>(par("streamManagerModule"),this);
}

void CUC::handleMessage(cMessage* msg) {
    // Check if message is StatusGroup
    StatusGroupMsg* sGroup = check_and_cast<StatusGroupMsg*>(msg);

    if (sGroup != nullptr) {
       // Log Group Info
       EV_INFO << "Received status group" << std::endl;

       // trigger callback to stream lifecycle manager
       streamManager->cucCallback(sGroup);

       // Free memory
       delete(msg);
    }
}

void CUC::registerStream(StreamIDTuple* streamIdentifier, IEEE8021QccStreamInfo* streamInfo) {
    // 1. Some dummy CUC functionality to generate a full request
    // 2. send CNC request to CNC
    Enter_Method("registerStream()");

    // Generate Talker Group message
    std::ostringstream oss;
    oss << "TalkerGroup_" << streamInfo->getUniqueID() << std::endl;
    TalkerGroupMsg* talkerGroup = streamInfo->generateTalkerGroup(oss.str());

    // Send Talker group
    EV_INFO << "Registering new Talker Group with CNC" << std::endl;
    send(talkerGroup, gate("cnc$o"));

    // Store knwoledge about stream
    // TODO: should be moved by querying lifecylceManager in handeMessage


    // Generate Talker Group message
    oss.clear();
    oss << "ListenerGroup_" << streamInfo->getUniqueID() << std::endl;
    ListenerGroupMsg* listenerGroup = streamInfo->generateListenerGroup(oss.str());

    // Send Listener group
    EV_INFO << "Registering new Listener Group with CNC" << std::endl;
    send(listenerGroup, gate("cnc$o"));

//}

}

