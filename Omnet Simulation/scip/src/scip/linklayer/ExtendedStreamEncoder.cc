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

#include "ExtendedStreamEncoder.h"
#include "inet/linklayer/common/PcpTag_m.h"
#include "inet/linklayer/common/VlanTag_m.h"
#include "inet/protocolelement/redundancy/StreamTag_m.h"
#include "inet/linklayer/common/DropEligibleTag_m.h"

#include "inet/linklayer/ethernet/common/EthernetMacHeader_m.h"
#include "inet/linklayer/ieee8021q/Ieee8021qTagHeader_m.h"

#include "inet/common/checksum/EthernetCRC.h"
#include "inet/linklayer/ethernet/common/Ethernet.h"

//namespace scip {

Define_Module(ExtendedStreamEncoder);

ExtendedStreamEncoder::ExtendedStreamEncoder() {
    // TODO Auto-generated constructor stub

}

ExtendedStreamEncoder::~ExtendedStreamEncoder() {
    // TODO Auto-generated destructor stub
}

void ExtendedStreamEncoder::initialize(int stage) {
    StreamEncoder::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        fcsMode = parseFcsMode(par("fcsMode"));
    }
}

void ExtendedStreamEncoder::configureMappings() {

    // Call super to configure basics
    StreamEncoder::configureMappings();

    // Reiterate the configured mappings, to add the removeVlanTag flag if needed
    auto mappingParameter = check_and_cast<cValueArray*>(
            par("mapping").objectValue());
    extendedMappings.resize(mappingParameter->size());

    for (int i = 0; i < mappings.size(); i++) {
        auto element = check_and_cast<cValueMap*>(
                mappingParameter->get(i).objectValue());

        ExtendedMapping &mapping = extendedMappings[i];
        mapping.base = &mappings[i];

        if (element->containsKey("removeVlanTag")) {
            mapping.removeVlanTag = element->get("removeVlanTag");
        } else {
            mapping.removeVlanTag = false;
        }
    }
}

void ExtendedStreamEncoder::processPacket(Packet *packet) {
    // Call normal handling of stream encoder
    StreamEncoder::processPacket(packet);

    // Overwrite functionality if the packet belongs to a mapping with the removeVlanTag flag set
    // Get stream name from tag
    auto streamReq = packet->findTag<StreamReq>();
    if (streamReq != nullptr) {

        for (auto &mapping : extendedMappings) {
            // Check which mapping the packet belongs to
            if (!strcmp(mapping.base->stream.c_str(),
                    streamReq->getStreamName())) {

                // Remove VLAN tag if flag is set
                if (mapping.removeVlanTag) {

                    // Remove Vlan Header from packet, since this is the egress switch
                    //removeIEEE8021qHeader(packet);
                    // Remove any indicators for Ieee8021q layer
                        packet->removeTagIfPresent<PcpReq>();
                        packet->removeTagIfPresent<VlanReq>();
                        packet->removeTagIfPresent<DropEligibleReq>();

                        // Change outer protocol from Ieee8021q to Ethernet
                        // First: remove old tag
                        packet->removeTagIfPresent<DispatchProtocolReq>();
                        // Then: add EthernetMac protocol tag
                        packet->addTagIfAbsent<DispatchProtocolReq>()->setProtocol(&Protocol::ethernetMac);
                }

                // Since the stream name is unique, stop searching through other mappings
                break;
            }
        }

    }

}

void ExtendedStreamEncoder::removeIEEE8021qHeader(Packet *packet) {
    // Switches only read headers, so we have to remove the Ieee8021q header here
    // The header stack currently is
    // MacHeader
    // Ieee8021qd
    // Ipv4
    // ...
    // -> Remove mac header, cut out Ieee8021qd header, reappend MacHeader (recalculate fcs?)
    packet->trimFront();

    // remove headers
    const auto &ethHeader = packet->popAtFront<EthernetMacHeader>();
    auto &ieee8021qHeader = packet->popAtFront<Ieee8021qTagEpdHeader>();

    // remove FCS trailer
    auto &oldEthFcs = packet->popAtBack<EthernetFcs>(ETHER_FCS_BYTES);

    // TODO: Delete VlanHeader via delete()?

    // recalculate FCS
    auto bytes = packet->peekDataAsBytes()->getBytes();
    uint32_t fcs = ethernetCRC(bytes.data(), packet->getByteLength());

    // generate new FCS trailer
    const auto &ethFcs = makeShared<EthernetFcs>();
    ethFcs->setFcs(fcs);
    ethFcs->setFcsMode(fcsMode);

    // Reattach ethernet header and FCS
    packet->insertAtFront(ethHeader);
    packet->insertAtBack(ethFcs);

    // Remove any indicators for Ieee8021q layer
    packet->removeTagIfPresent<PcpReq>();
    packet->removeTagIfPresent<VlanReq>();
    packet->removeTagIfPresent<DropEligibleReq>();

}

//} // end namespace scip
