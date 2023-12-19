/*
 * StreamClassifier.h
 *
 *  Created on: May 22, 2022
 *      Author: moritz
 */

#include "StreamClassifier.h"
#include <stdlib.h>
#include <sstream>

#include "inet/common/ModuleAccess.h"

//namespace scip {

Define_Module(StreamClassifier);

void StreamClassifier::initialize() {
    doRhebo = par("doRhebo");
}

void StreamClassifier::classifyStream(StreamIDTuple* stream, StreamDbEntry* entry) {
    Enter_Method("classifyStream()");

    /*
    streamInfo->pcap->closePcap();
    EV_INFO << "Finished recording Pcap information. Starting Classification!" << std::endl;

    if (doRhebo) {
        //Generate string identifier for file
        std::ostringstream command;
        command << "./classify.sh " << streamInfo->pcapFile;

        // Start classification pipeline
        // TODO: add disable feature to get faster runs if classification already exists
        std::system(command.str().c_str());
    }


    // Parse classification Info
    EV_INFO << "Finished Classification!" << std::endl;

    // retrieve classifier information
    //parseXML(streamIdentifier, streamInfo);
*/
}

void StreamClassifier::parseXML(StreamIDTuple* stream, StreamDbEntry* entry) {
/*

    const char* xmlPath = "/streams/";
    cXMLElement* classifierOutput = getEnvir()->getXMLDocument(streamInfo->xmlFile.c_str(), xmlPath);


    for (cXMLElement* stream : classifierOutput->getChildren()) {

        // First: Get Mapping Ip-5 tuple for lookup
        // get Ip string from XML
        const char* ipSrcChars = stream->getFirstChildWithTag("srcIp")->getNodeValue();
        const char* ipDstChars = stream->getFirstChildWithTag("dstIp")->getNodeValue();

        // Convert Ip strings to IpAddr object and store pointer
        Ipv4Address srcAddr = *new Ipv4Address(ipSrcChars);
        Ipv4Address dstAddr = *new Ipv4Address(ipDstChars);

        // Get Port numbers from XML
        unsigned short srcPort = (unsigned short) std::strtoul(stream->getFirstChildWithTag("srcPort")->getNodeValue(), NULL, 10);
        unsigned short dstPort = (unsigned short) std::strtoul(stream->getFirstChildWithTag("dstPort")->getNodeValue(), NULL, 10);

        // Get nextProtocol from xml as int
        int nextProtoInt = (int) std::strtoul(stream->getFirstChildWithTag("l4Proto")->getNodeValue(), nullptr, 10);
        // Convert to IpProtocolId enum
        IpProtocolId l4Proto = static_cast<IpProtocolId>(nextProtoInt);

        StreamID xmlTuple = {
                srcAddr,
                dstAddr,
                srcPort,
                dstPort,
                l4Proto
        };

        if (xmlTuple == *streamIdentifier) {
            // TODO: also check if periodic
            // Stream from XML matches stream that was tried to be identified
            cXMLElement* characteristics = stream->getFirstChildWithTag("streamCharacteristics");

            // Convert text from XML to float
            float interval = std::atof(characteristics->getFirstChildWithTag("meanPeriod")->getNodeValue());

            // Convert XML text to uint16_t
            uint16_t maxFrameSize = (uint16_t) std::strtoul(characteristics->getFirstChildWithTag("maxFrameLength")->getNodeValue(), nullptr, 10);
            uint16_t maxFramesPerInterval = (uint16_t) std::strtoul(characteristics->getFirstChildWithTag("maxFramesPerInterval")->getNodeValue(), nullptr, 10);

            // Get mac address from XML
            MacAddress* mac = new MacAddress(stream->getAttribute("mac"));

            // Store classifier Info for CUC request
            streamInfo->classInfo = {
                    { // EndStationInterfaces
                            mac,
                            "main"
                    },
                    { // Traffic Specification
                            interval,
                            maxFramesPerInterval,
                            maxFrameSize,
                            0 // No transmission selection algorithm on talker
                    },
                    { // UserToNetworkRequirements
                            0,
                            2000
                    }
            };

        }

    }

    // No entry in the XML matches the given stream identifier
    // streamInfo->state = classification_failed;
*/

//}


}//Namespace SCIPFramework
