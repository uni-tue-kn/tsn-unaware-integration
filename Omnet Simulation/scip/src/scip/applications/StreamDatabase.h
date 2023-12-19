/*
 * StreamDatabase.h
 *
 *  Created on: May 22, 2022
 *      Author: moritz
 */

//#include "inet/linklayer/ethernet/EtherFrame_m.h"
//#include "inet/common/packet/Packet.h"

#ifndef STREAMDATABASE_H
#define STREAMDATABASE_H

#include <omnetpp.h>
#include <unordered_map>

#include "inet/networklayer/ipv4/Ipv4Header_m.h"
#include "inet/common/packet/recorder/PcapWriter.h"
#include "string"
#include "scip/applications/base/IStreamDatabase.h"

//#include "scip/applications/base/IStreamDatabase.h"

using namespace omnetpp;
using namespace inet;
//using namespace nesting;

#include "scip/core/TSNStream.h"
using namespace scip;

//namespace scip {




class StreamDatabase : public cSimpleModule, public IStreamDatabase
{

    public:
        StreamDatabase();
        virtual ~StreamDatabase();
        StreamDbEntry* lookupStream(StreamIDTuple* streamIdentifier);
        void createStream(StreamIDTuple& streamIdentifier);
        void removeStream(StreamIDTuple* streamIdentifier);
        StreamDbEntry* lookupStreamUniqueID(uint16_t id);


    protected:
        void initialize(int stage);
    private:
        std::unordered_map<StreamIDTuple, StreamDbEntry> streamDB;

};
//} // namespace SCIPFramework

#endif

