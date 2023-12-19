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

#include "SwitchConfigurator.h"
#include "scip/messages/switchConfigurationMsg_m.h"

//namespace scip {

Define_Module(SwitchConfigurator);

SwitchConfigurator::SwitchConfigurator() {
    // TODO Auto-generated constructor stub

}

SwitchConfigurator::~SwitchConfigurator() {
    // TODO Auto-generated destructor stub
}

void SwitchConfigurator::writeConfig(StreamIDTuple *stream, CBMapping *mapping,
        uint16_t uniqueID, std::string streamName) {
    Enter_Method("writeConfig()");

    // Broadcast config to all switches
    // One broadcast for each switch connected
    // The switches select the relevant messages based on their configured ID

    // Select relevant switch configuration from parameters
    std::unordered_map<uint16_t, std::vector<int>>::iterator entry =
            switchConfig.find(uniqueID);

    // Check if lookup did return a value
    if (entry == switchConfig.end()) {
        // entry not found
        EV_ERROR << "Did not find a valid configuration for ID: " << uniqueID
                        << " . Skipping configuration!";
        return;
    }

    // entry found, return information pointer
    std::vector<int>* confs = &(entry->second);

    // Broadcast one message per entry
    for (uint8_t i = 0; i < confs->size(); i++) {

        // 0 means do not configure switch
        if ((*confs)[i] == 0) {
            continue;
        }

        AddConfigurationMsg *confMsg = new AddConfigurationMsg();

        // Switch ID == index in array
        confMsg->setSwitchID(i);
        confMsg->setStream(streamName.c_str());

        // Stream Identification
        confMsg->setSrcAddr(stream->srcAddr->getInt());
        confMsg->setDstAddr(stream->dstAddr->getInt());

        confMsg->setSrcPort(stream->srcPort);
        confMsg->setDstPort(stream->dstPort);

        confMsg->setL4Proto(stream->l4Proto);

        // Check if tag should be removed at this switch
        if ((*confs)[i] == 2) {
            confMsg->setRemoveVlanTag(true);
        }

        // Mapping
        confMsg->setVlanID(mapping->vlanID);
        confMsg->setPcp(mapping->pcp);

        // Send to all switches
        for (int j = 0; j < numSwitches; j++) {
                send(confMsg->dup(), gate("switches", j));
            }

        delete(confMsg);
    }
}

void SwitchConfigurator::removeConfig(std::string stream) {
    Enter_Method("removeConfig()");
    RemoveConfigurationMsg *confMsg = new RemoveConfigurationMsg();

    confMsg->setStream(stream.c_str());

    // Send to all switches
    for (int j = 0; j < numSwitches; j++) {
            send(confMsg->dup(), gate("switches", j));
    }

    delete(confMsg);
}


void SwitchConfigurator::initialize() {

    numSwitches = par("numSwitches");

    cValueArray *streamPar = check_and_cast<cValueArray*>(
            par("streams").objectValue());
    for (int i = 0; i < streamPar->size(); i++) {

        cValueMap *element = check_and_cast<cValueMap*>(
                streamPar->get(i).objectValue());

        // Get config for switches
        cValueArray *switchConfigPar = check_and_cast<cValueArray*>(
                element->get("switches").objectValue());

        std::vector<int> switchConfigs;
        switchConfigs.resize(switchConfigPar->size());

        // Read int values into vector
        // TODO: improve efficiency with a cast instead of for loop?
        for (int j = 0; j < switchConfigPar->size(); j++) {
            switchConfigs[j] = switchConfigPar->get(j).intValue();
        }

        uint16_t uniqueID = (unsigned short) element->get("uniqueID");

        // Create new entry in HashMap
        std::pair<uint16_t, std::vector<int>> newPair(uniqueID, switchConfigs);
        switchConfig.insert(newPair);

    }
}

//} // end namespace scip
