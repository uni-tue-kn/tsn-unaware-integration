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

// General TODO: add more CNC behaviour

#include "CNC.h"

Define_Module(CNC);

CNC::CNC() {
    // TODO Auto-generated constructor stub
}

CNC::~CNC() {
    // TODO Auto-generated destructor stub
}

void CNC::initialize(int stage) {
    if (stage == INITSTAGE_LOCAL) {
        knownEndStations = { };
        streams = { };

        // Get parameter
        cValueArray *streamParameter = check_and_cast<cValueArray*>(
                par("streams").objectValue());

        for (int i = 0; i < streamParameter->size(); i++) {
            cValueMap *streamMapping = check_and_cast<cValueMap*>(
                    streamParameter->get(i).objectValue());

            // Parse mapping from NED parameter
            CBMapping newMapping = { };
            newMapping.vlanID =
                    streamMapping->containsKey("vlanID") ?
                            streamMapping->get("vlanID").intValue() : 0;
            newMapping.pcp =
                    streamMapping->containsKey("pcp") ?
                            streamMapping->get("pcp").intValue() : 0;

            if (!streamMapping->containsKey("uniqueID")) {
                EV_ERROR << "CNC stream entries have to have the key 'streamID'"
                                << std::endl;
            } else {
                // Create new entry in HashMap
                std::pair<uint16_t, CBMapping> newPair(
                        streamMapping->get("uniqueID").intValue(), newMapping);
                streams.insert(newPair);
            }

        }

    }

}

void CNC::handleMessage(cMessage *msg) {

    // Check if message is TalkerGroup
    TalkerGroupMsg *tGroup = dynamic_cast<TalkerGroupMsg*>(msg);

    if (tGroup != nullptr) {
        // Log Group Info
        EV_INFO << "Received talker group" << " srcMAC: "
                       << tGroup->getMacAdress() << " ID: "
                       << tGroup->getUniqueID() << " Rank: "
                       << tGroup->getStreamRank() << std::endl;

        // Call message handling
        handleTalkerGroup(tGroup);

        // Free memory and stop handling
        delete(msg);
        return;
    }

    // Check if message is ListenerGroup
    ListenerGroupMsg *lGroup = dynamic_cast<ListenerGroupMsg*>(msg);

    if (lGroup != nullptr) {
        // Log Group Info
        EV_INFO << "Received listener group" << " srcMAC: "
                       << lGroup->getMacAdress() << " ID: "
                       << lGroup->getUniqueID() << std::endl;

        // Call message handling
        handleListenerGroup(lGroup);

        // Free memory and stop handling
        delete(msg);
        return;
    }

}

void CNC::handleTalkerGroup(TalkerGroupMsg *tGroup) {

    // Get stream ID from message
    uint16_t uniqueID = tGroup->getUniqueID();

    // Lookup ID in internap database
    std::unordered_map<uint16_t, CNCGroupEntry>::iterator entry =
            knownEndStations.find(uniqueID);

    // Check if lookup did return a value
    if (entry == knownEndStations.end()) {
        // entry not found, create new one
        addNewStream(uniqueID, tGroup->getMacAdress(), true);
    } else {
        // entry found, return information pointer

        CNCGroupEntry* stream = &entry->second;

        // Store talker information
        stream->knownTalker = tGroup->getMacAdress();

        // Check if there is already a listener group present
        if (stream->knownListeners.size() > 0) {
            // Notify stream lifecycle manager that new stream is registered
            sendStatusGroup(uniqueID);
        }
    }
}

// TODO: more flexible system, handle multiple listeners better
// Currently, the stream lifecylce manager (CUC) is informed as soon as there
//  talker and at least one listener is known
// Updates for additional listeners could caus problem
void CNC::handleListenerGroup(ListenerGroupMsg *lGroup) {

    // Get stream ID from message
    uint16_t uniqueID = lGroup->getUniqueID();

    // Lookup ID in internap database
    std::unordered_map<uint16_t, CNCGroupEntry>::iterator entry =
            knownEndStations.find(uniqueID);

    // Check if lookup did return a value
    if (entry == knownEndStations.end()) {
        // entry not found, create new one
        addNewStream(uniqueID, lGroup->getMacAdress(), false);
    } else {
        // entry found
        CNCGroupEntry* stream = &entry->second;

        // Store talker information
        stream->knownListeners.push_back(lGroup->getMacAdress());

        // Check if there is already a talker group present
        if (stream->knownTalker != 0) {
            // Notify stream lifecycle manager that new stream is registered
            sendStatusGroup(uniqueID);
        }
    }
}

void CNC::sendStatusGroup(uint16_t uniqueID) {
    // TODO: also fill other fields, such that they make sense.
    //   A lot of this is just dummy implementations that do not simulate real bahaviour
    //   Todo: Failure Codes and handling, StatusCodes, accumulatedLatency, ...

    std::ostringstream oss;
    oss << "StatusGroupID: " << uniqueID;

    StatusGroupMsg *statusGroup = new StatusGroupMsg(oss.str().c_str());

    // Lookup ID in internal database
    std::unordered_map<uint16_t, CBMapping>::iterator entry =
                streams.find(uniqueID);

    // Check if lookup did return a value
    if (entry == streams.end()) {
        EV_ERROR << "Did not find a corresponding parameter entry for this stream. sending no status group!" << std::endl;
    } else {
        CBMapping* mapping = &entry->second;
        statusGroup->setUniqueID(uniqueID);
        statusGroup->setVlanID(mapping->vlanID);
        statusGroup->setPcp(mapping->pcp);

        send(statusGroup, gate("scip$o"));
    }
}

void CNC::addNewStream(uint16_t uniqueID, uint64_t mac, bool isTalker) {

    CNCGroupEntry newEntry;

    if (isTalker) {
        newEntry.knownTalker = mac;
    } else {
        newEntry.knownListeners.push_back(mac);
    }

    std::pair<uint16_t, CNCGroupEntry> newPair(uniqueID, newEntry);
    knownEndStations.insert(newPair);
}




