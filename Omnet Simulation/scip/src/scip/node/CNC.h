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

#ifndef SCIP_NODE_CNC_H_
#define SCIP_NODE_CNC_H_

#include <omnetpp.h>
#include <unordered_map>
#include "scip/messages/streamReservation_m.h"
#include "scip/core/TSNStream.h"


using namespace omnetpp;
using namespace scip;

struct CNCGroupEntry {
    std::vector<uint64_t> knownListeners;
    uint64_t knownTalker = 0;
};



class CNC : public cSimpleModule {
public:
    CNC();
    virtual ~CNC();
protected:
    void initialize(int stage);
    void handleMessage(cMessage* msg);
    void handleTalkerGroup(TalkerGroupMsg* tGroup);
    void handleListenerGroup(ListenerGroupMsg* tGroup);
    void sendStatusGroup(uint16_t uniqueID);
    void addNewStream(uint16_t uniqueID, uint64_t mac, bool isTalker);

    // Key: stream uniqueID
    std::unordered_map<uint16_t, CNCGroupEntry> knownEndStations;
    // Key: stream uniqueID
    std::unordered_map<uint16_t, CBMapping> streams;


};

#endif /* SCIP_NODE_CNC_H_ */
