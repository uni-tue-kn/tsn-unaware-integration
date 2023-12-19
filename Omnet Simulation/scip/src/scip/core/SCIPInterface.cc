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

#include "SCIPInterface.h"
#include "inet/networklayer/common/IpProtocolId_m.h"
//#include <cdynamicexpression.h>
#include "scip/messages/switchConfigurationMsg_m.h"

#include <sstream>

//namespace scip {

Define_Module(SCIPInterface);

SCIPInterface::SCIPInterface() {
    // TODO Auto-generated constructor stub
}

SCIPInterface::~SCIPInterface() {
    // TODO Auto-generated destructor stub
}

void SCIPInterface::initialize(int stage) {
    // TODO: add parsing and adding of static mappings from parameter

    if (stage == INITSTAGE_LOCAL) {
        // Initialize references to TSN stream encoder, decoder and identifier modules
        // They can later be used to alter the mutable mapping parameters
        //this->streamIdentifier = getModuleFromPar<cModule>(par("streamIdentifierModule"), this);
        streamEncoder = getModuleFromPar<cModule>(par("streamEncoderModule"),
                this);
        streamDecoder = getModuleFromPar<cModule>(par("streamDecoderModule"),
                this);

        switchID = par("switchID");
    }

}

void SCIPInterface::registerStream(StreamIDTuple *id, CBMapping *mapping,
        std::string stream, bool removeVlanTag) {

    // Add new mapping to StreamEncoder and StreamDecoder
    addToEncoderMapping(stream, mapping->pcp, mapping->vlanID, removeVlanTag);
    addToDecoderMapping(id, stream);

}

void SCIPInterface::deregisterStream(std::string stream) {
    removeFromCoderMapping(streamEncoder, stream);
    removeFromCoderMapping(streamDecoder, stream);
}

void SCIPInterface::addToDecoderMapping(StreamIDTuple *id, std::string stream) {

    // TODO: maybe extract reference at initialization if pointers are static
    // fetch mapping parameter reference
    cPar *mappingPar = &(this->streamDecoder->par("mapping"));

    // get Value of parameter
    cValueArray *mappings = check_and_cast<cValueArray*>(
            mappingPar->objectValue());

    // Check if retrieval successfull
    // TODO: Error handling
    if (mappings != nullptr) {
        // Build new entry
        cValueMap *newMapping = new cValueMap();

        // Build filter string.
        // This is the easiest way to generate a packet filter
        std::stringstream ss;

        ss << "ipv4.destAddress.str() == '" << id->dstAddr->str() << "' && ";
        ss << "ipv4.srcAddress.str() == '" << id->srcAddr->str() << "' && ";

        if (id->l4Proto == 6) {
            // TCP
            ss << "has(tcp) && " << "tcp.destPort == " << id->dstPort << " && "
                    << "tcp.srcPort == " << id->srcPort;
        }

        if (id->l4Proto == 17) {
            // UDP
            ss << "has(udp) && " << "udp.destPort == " << id->dstPort << " && "
                    << "udp.srcPort == " << id->srcPort;
        }

        // Create filter epxression object to insert into mapping
        std::string filterString = ss.str();
        cOwnedDynamicExpression *dynExpr = new cOwnedDynamicExpression();
        dynExpr->parse(filterString.c_str());

        // Add values to new mapping
        newMapping->set("packetFilter", dynExpr);
        newMapping->set("stream", stream);

        // Add to object containing already loaded mappings
        mappings->add(newMapping);

        // Update mutable parameter to trigger change handling function
        mappingPar->setObjectValue(mappings);

    } else {
        EV_ERROR << "Cannot access parameter 'mapping' of "
                        << this->streamEncoder
                        << " . Is the *Module path parameter set correctly?"
                        << std::endl;
    }
}

void SCIPInterface::removeFromCoderMapping(cModule *target,
        std::string stream) {
    cPar *mappingPar = &(target->par("mapping"));

    // get Value of parameter
    cValueArray *mappings = check_and_cast<cValueArray*>(
            mappingPar->objectValue());

    // Check if retrieval successfull
    // TODO: Error handling
    if (mappings != nullptr) {
        for (int i = 0; i < mappings->size(); i++) {
            // Get single element from list
            auto element = check_and_cast<cValueMap*>(
                    mappings->get(i).objectValue());

            // Search for element with given UNIQUE stream name
            if (element->get("stream").str() == stream) {
                // Remove element and shift down
                mappings->erase(i);

                // Mapping entries are unique by stream name, so stop after deletion
                return;
            }
        }
    }
}

void SCIPInterface::addToEncoderMapping(std::string stream, int pcp, int vlan,
        bool removeVlanTag) {
    // fetch mapping parameter reference
    cPar *mappingPar = &(streamEncoder->par("mapping"));

    // get Value of parameter
    cValueArray *mappings = check_and_cast<cValueArray*>(
            mappingPar->objectValue());

    // Check if retrievak successfull
    // TODO: Error handling
    if (mappings != nullptr) {
        // Build new entry
        cValueMap *newMapping = new cValueMap();
        newMapping->set("pcp", pcp);
        newMapping->set("vlan", vlan);
        newMapping->set("stream", stream);

        // Check if encoder should remove VLAN tag rather than add it
        // Note: this will cause the stream encoder to ignore the vlan and pcp values
        if (removeVlanTag) {
            newMapping->set("removeVlanTag", true);
        }

        // Add to object containing already loaded mappings
        mappings->add(newMapping);

        // Update mutable parameter to trigger change handling functionRelay
        mappingPar->setObjectValue(mappings);
    } else {
        EV_ERROR << "Cannot access parameter 'mapping' of " << streamEncoder
                        << " . Is the *Module path parameter set correctly?"
                        << std::endl;
    }

}

void SCIPInterface::handleMessage(cMessage *msg) {

    // Check if message is a new configuration
    AddConfigurationMsg *addConfigMsg = dynamic_cast<AddConfigurationMsg*>(msg);
    if (addConfigMsg != nullptr) {

        // Check if message is meant for this switch
        if (addConfigMsg->getSwitchID() == switchID) {

            // Build data structures needed for registerStream function
            StreamIDTuple id = { new Ipv4Address(addConfigMsg->getSrcAddr()),
                    new Ipv4Address(addConfigMsg->getDstAddr()),
                    addConfigMsg->getSrcPort(), addConfigMsg->getDstPort(),
                    static_cast<IpProtocolId>(addConfigMsg->getL4Proto()) };
            CBMapping mapping = { addConfigMsg->getVlanID(),
                    addConfigMsg->getPcp(), addConfigMsg->getDe() };

            // Add stream to en- and decoder
            registerStream(&id, &mapping, addConfigMsg->getStream(),
                    addConfigMsg->getRemoveVlanTag());
        }

        // Stop processign message
        delete msg;
        return;
    }

    // Check if message is signals to delete old entry
    RemoveConfigurationMsg *rmConfigMsg =
            check_and_cast<RemoveConfigurationMsg*>(msg);
    if (rmConfigMsg != nullptr) {

        // remove config from switch
        deregisterStream(rmConfigMsg->getStream());

        // Stop processign message
        delete msg;
        return;
    }

}

//} // end namespace scip

