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

#ifndef SCIP_LINKLAYER_EXTENDEDSTREAMENCODER_H_
#define SCIP_LINKLAYER_EXTENDEDSTREAMENCODER_H_

#include <omnetpp.h>
#include "inet/protocolelement/redundancy/StreamEncoder.h"
#include "scip/core/TSNStream.h"
#include "inet/linklayer/common/FcsMode_m.h"

using namespace inet;
using namespace omnetpp;
using namespace scip;

//namespace scip {
class ExtendedStreamEncoder : public StreamEncoder {
public:
    ExtendedStreamEncoder();
    virtual ~ExtendedStreamEncoder();
    void addMapping(StreamIDTuple* id, CBMapping* newMapping);
    virtual void initialize(int stage);
protected:
    FcsMode fcsMode = FCS_MODE_UNDEFINED;
    void configureMappings() override;
    void processPacket(Packet *packet) override;
    void removeIEEE8021qHeader(Packet* packet);

    struct ExtendedMapping {
        Mapping* base;
        bool removeVlanTag;
    };

    std::vector<ExtendedMapping> extendedMappings;
};
//}

#endif /* SCIP_LINKLAYER_EXTENDEDSTREAMENCODER_H_ */
