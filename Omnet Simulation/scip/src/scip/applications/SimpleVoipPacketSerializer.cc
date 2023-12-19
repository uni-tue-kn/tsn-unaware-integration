#include "inet/common/Endian.h"
#include "inet/common/packet/serializer/ChunkSerializerRegistry.h"
#include "scip/applications/SimpleVoipPacketSerializer.h"
#include "inet/applications/voip/SimpleVoipPacket_m.h"

namespace inet {

Register_Serializer(SimpleVoipPacket, SimpleVoipPacketSerializer);

void SimpleVoipPacketSerializer::serialize(MemoryOutputStream &stream,
        const Ptr<const Chunk> &chunk) const {

    // Cast chunk to VoipPacket in order to access fields
    const auto &simpleVoipPacket = staticPtrCast<const SimpleVoipPacket>(chunk);

    // Get total length field
    uint16_t totalLengthField = simpleVoipPacket->getTotalLengthField();
    stream.writeUint16Be(totalLengthField);

    // Get talkspurt ID
    unsigned int talkspurtID = simpleVoipPacket->getTalkspurtID();
    stream.writeUint32Be(talkspurtID);

    // Get talkspurtNumPackets
    unsigned int talkspurtNumPackets =
            simpleVoipPacket->getTalkspurtNumPackets();
    stream.writeUint32Be(talkspurtNumPackets);

    // Get packetID
    unsigned int packetID = simpleVoipPacket->getPacketID();
    stream.writeUint32Be(packetID);

    // Get voipTimestamp
    int64_t voipTimestamp = simpleVoipPacket->getVoipTimestamp().raw();
    stream.writeUint64Be(voipTimestamp);

    // Get voipTimestamp
    int64_t voiceDuration = simpleVoipPacket->getVoiceDuration().raw();
    stream.writeUint64Be(voiceDuration);

    // Get length of data in VoIP packet
    // FIXME: This is really hacky padding, the totalLengthField is 40 bytes, but the message fields are only 30 bytes in total
    //      There should be an udnerlying reason, but I cannot find it at the moment
    uint16_t dataLength = totalLengthField - 30;
    for (int i = 0; i < dataLength; i++) {
        stream.writeByte(0);
    }

}

const Ptr<Chunk> SimpleVoipPacketSerializer::deserialize(
        MemoryInputStream &stream) const {

    auto simpleVoipPacket = makeShared<SimpleVoipPacket>();

    // First, read bytes in to variables
    uint16_t totalLengthField = stream.readUint16Be();
    unsigned int talkspurtID = stream.readUint32Be();
    unsigned int talkspurtNumPackets = stream.readUint32Be();
    unsigned int packetID = stream.readUint32Be();
    simtime_t voipTimestamp = simtime_t(stream.readUint64Be());
    simtime_t voiceDuration = simtime_t(stream.readUint64Be());

    // Read padding
    // FIXME: This is really hacky, the totalLengthField is 40 bytes, but the message fields are only 30 bytes in total
    //      There should be an udnerlying reason, but I cannot find it at the moment
    uint16_t dataLength = totalLengthField - 30;
    for (int i = 0; i < dataLength; i++) {
        stream.readByte();
    }

    // Set values of packet class
    simpleVoipPacket->setTotalLengthField(totalLengthField);
    simpleVoipPacket->setTalkspurtID(talkspurtID);
    simpleVoipPacket->setTalkspurtNumPackets(talkspurtNumPackets);
    simpleVoipPacket->setPacketID(packetID);

    simpleVoipPacket->setVoipTimestamp(voipTimestamp);
    simpleVoipPacket->setVoiceDuration(voiceDuration);

    return simpleVoipPacket;
}

} // namespace inet
