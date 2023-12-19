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

#ifndef SCIP_APPLICATIONS_BASE_ISTREAMDATABASE_H_
#define SCIP_APPLICATIONS_BASE_ISTREAMDATABASE_H_

#include <omnetpp.h>
#include "inet/common/packet/Packet.h"
#include "scip/core/TSNStream.h"
#include "inet/common/packet/recorder/PcapWriter.h"
#include "scip/core/IEEE8021Qcc.h"
#include "scip/messages/streamTimeout_m.h"

using namespace omnetpp;
using namespace inet;
using namespace scip;


struct StreamDbEntry {
       CBMapping mapping;
       StreamState state;
       unsigned int packetCount;
       PcapWriter* pcap;
       std::string pcapFile;
       std::string xmlFile;
       IEEE8021QccStreamInfo* streamInfo;
       StreamTimeoutMsg* timeoutMsg;
       std::string name;
};


class IStreamDatabase {
public:
    virtual ~IStreamDatabase() = default;
    // Functions a stream database has to implement
    virtual StreamDbEntry* lookupStream(StreamIDTuple* streamIdentifier) = 0;
    virtual void createStream(StreamIDTuple& streamIdentifier) = 0;
    virtual void removeStream(StreamIDTuple* streamIdentifier) = 0;
    virtual StreamDbEntry* lookupStreamUniqueID(uint16_t id) = 0;
};

#endif /* SCIP_APPLICATIONS_BASE_ISTREAMDATABASE_H_ */
