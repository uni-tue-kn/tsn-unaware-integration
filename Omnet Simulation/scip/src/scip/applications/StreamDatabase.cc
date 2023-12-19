/*
 * StreamDatabase.h
 *
 *  Created on: May 22, 2022
 *      Author: moritz
 */

#include "StreamDatabase.h"
#include <sstream>

//namespace scip {

Define_Module(StreamDatabase);

StreamDatabase::~StreamDatabase() {

}

StreamDatabase::StreamDatabase() {
    // TODO Auto-generated constructor stub
}

void StreamDatabase::initialize(int stage) {
    if (stage == INITSTAGE_LOCAL) {
        // Initialize empty stream Database
        streamDB = { };
    }
}

StreamDbEntry* StreamDatabase::lookupStream(StreamIDTuple *streamIdentifier) {
    Enter_Method("lookupStream()");

     // Perform lookup on unordered map
     std::unordered_map<StreamIDTuple, StreamDbEntry>::iterator entry = streamDB.find(*streamIdentifier);

     // Check if lookup did return a value
     if (entry == streamDB.end()) {
     // entry not found
     return nullptr;
     } else {
     // entry found, return information pointer
     return &entry->second;
     }

    return nullptr;
}

void StreamDatabase::removeStream(StreamIDTuple *stream) {
    Enter_Method("removeStream()");
    // TODO: implement
}

StreamDbEntry* StreamDatabase::lookupStreamUniqueID(uint16_t id) {
    // TODO: could be more efficient with some sorft of alternative lookup map

    // Iterate over hash map entries
    std::unordered_map<StreamIDTuple, StreamDbEntry>::iterator it;
    for (it = streamDB.begin(); it != streamDB.end(); it++)
    {

        // Fetch entry value
        StreamDbEntry* entry = &it->second;

        if (id == entry->streamInfo->getUniqueID()) {
            return entry;
        }


    }

    // No entry found during lookup
    return nullptr;

}

void StreamDatabase::createStream(StreamIDTuple &stream) {
    // TODO: read stream unique ID from configuration
    Enter_Method("createStream()");
    // Create Pcap Recorder
    PcapWriter *writer = new PcapWriter();

    //Generate string identifier for file
    std::ostringstream oss;
    oss << "pcaps/" << std::to_string(std::hash<StreamIDTuple> { }(stream))
            << ".pcap";

    std::ostringstream ossXml;
    ossXml << "pcaps/" << std::to_string(std::hash<StreamIDTuple> { }(stream))
            << ".pcap.xml";

    // Open save file under hash as name
    // 65535 is the max packet size
    writer->open(oss.str().c_str(), 65535);
    // always flush new packets to file
    writer->setFlush(true);

    // Create stream information holder
    StreamDbEntry newEntry = {
            { },
            pending,
            1,
            writer,
            oss.str(),
            ossXml.str(),
            new IEEE8021QccStreamInfo(),
            nullptr,
            ""
    };

    // Create new entry in HashMap
    std::pair<StreamIDTuple,StreamDbEntry>newPair(stream, newEntry);
    streamDB.insert(newPair);



//}

}
