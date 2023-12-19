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

#ifndef SCIP_CORE_SCIPINTERFACE_H_
#define SCIP_CORE_SCIPINTERFACE_H_

#include <omnetpp.h>
#include "inet/common/ModuleAccess.h"
#include "scip/core/TSNStream.h"
#include "inet/common/packet/PacketFilter.h"

using namespace omnetpp;
using namespace inet;
using namespace scip;

//namespace scip {


class SCIPInterface : public cSimpleModule {
public:
    SCIPInterface();
    virtual ~SCIPInterface();
    virtual void initialize(int stage);
    virtual void handleMessage(cMessage* msg);
private:
    cModule* streamEncoder;
    cModule* streamDecoder;
    // DEBUG: timed message
    cMessage* timer;
    int switchID;

    //cModule* streamIdentifier;
    void registerStream(StreamIDTuple* id, CBMapping* mapping, std::string name, bool removeVlanTag = false);
    void addToEncoderMapping(std::string stream, int pcp, int vlan, bool removeVlanTag);
    void addToDecoderMapping(StreamIDTuple* id, std::string stream);
    void deregisterStream(std::string stream);
    void removeFromCoderMapping(cModule* target, std::string stream);
};

//} // end namespace scip

#endif /* SCIP_CORE_SCIPINTERFACE_H_ */
