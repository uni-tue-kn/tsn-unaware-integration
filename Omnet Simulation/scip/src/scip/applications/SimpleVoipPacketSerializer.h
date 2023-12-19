#include "inet/common/packet/serializer/FieldsChunkSerializer.h"


namespace inet {
/**
 * Converts between SimpleVoipPacket and binary (network byte order) SimpleVoipPacket.
 */

class INET_API SimpleVoipPacketSerializer : public FieldsChunkSerializer
{
    protected:
        virtual void serialize(MemoryOutputStream& stream, const Ptr<const Chunk>& chunk) const override;
        virtual const Ptr<Chunk> deserialize(MemoryInputStream& stream) const override;
    public:
        SimpleVoipPacketSerializer() : FieldsChunkSerializer() {}
};

} // namespace inet

