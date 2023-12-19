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

#ifndef CORE_TSNSTREAM_H_
#define CORE_TSNSTREAM_H_

// Includes
#include <omnetpp.h>
#include "inet/networklayer/ipv4/Ipv4Header_m.h"

// Namespaces
using namespace omnetpp;
using namespace inet;



namespace scip {

struct CBMapping {
    uint16_t vlanID;
    uint8_t pcp;
    bool de;
};

struct StreamIDTuple {
    Ipv4Address* srcAddr;
    Ipv4Address* dstAddr;
    unsigned short srcPort;
    unsigned short dstPort;
    IpProtocolId l4Proto;

    // Add method for comparison of two StreamIDs via '==' operator
    bool operator==(const StreamIDTuple second) const {
        bool srcIpMatch, dstIpMatch, protoMatch, srcPortMatch, dstPortMatch;

        // Check if IPs match
        srcIpMatch = this->srcAddr->equals(*(second.srcAddr));
        dstIpMatch = this->dstAddr->equals(*(second.dstAddr));

        // Check if ports match
        srcPortMatch = (this->srcPort == second.srcPort);
        dstPortMatch = (this->dstPort == second.dstPort);

        // Check if layer4 proto matches
        protoMatch = (this->l4Proto == second.l4Proto);

        return (srcIpMatch && dstIpMatch && srcPortMatch && dstPortMatch && protoMatch);
    };
};

} // end namespace scip

// Add hash function for StreamID, required for usage as key in hash maps
namespace std {
template <>
struct hash<scip::StreamIDTuple> {
    size_t operator()(const scip::StreamIDTuple& tuple) const {
        using std::hash;
        // Suggested by Josh Bloch in "Effective Java"
        // Used to build hash over multiple values
        size_t result = 17;
        result = result * 31 + hash<int>()(tuple.srcAddr->getInt());
        result = result * 31 + hash<int>()(tuple.dstAddr->getInt());
        result = result * 31 + hash<short>()(tuple.srcPort);
        result = result * 31 + hash<short>()(tuple.dstPort);
        result = result * 31 + hash<short>()(tuple.l4Proto);
        return result;
    }
};
} //namespace std

enum StreamState {
    pending = -1,
    awaiting_classification = 0,
    classification_failed = 1,
    classification_successfull = 2,
    awaiting_reservation = 3,
    established = 4,
    stopped = 5,
    unfit = 6
};

#endif /* CORE_TSNSTREAM_H_ */
