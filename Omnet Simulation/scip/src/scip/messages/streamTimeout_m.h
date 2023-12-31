//
// Generated file, do not edit! Created by opp_msgtool 6.0 from src/scip/messages/streamTimeout.msg.
//

#ifndef __STREAMTIMEOUT_M_H
#define __STREAMTIMEOUT_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// opp_msgtool version check
#define MSGC_VERSION 0x0600
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgtool: 'make clean' should help.
#endif

class StreamTimeoutMsg;
/**
 * Class generated from <tt>src/scip/messages/streamTimeout.msg:20</tt> by opp_msgtool.
 * <pre>
 * packet StreamTimeoutMsg
 * {
 *     uint16_t uniqueID;
 * }
 * </pre>
 */
class StreamTimeoutMsg : public ::omnetpp::cPacket
{
  protected:
    uint16_t uniqueID = 0;

  private:
    void copy(const StreamTimeoutMsg& other);

  protected:
    bool operator==(const StreamTimeoutMsg&) = delete;

  public:
    StreamTimeoutMsg(const char *name=nullptr, short kind=0);
    StreamTimeoutMsg(const StreamTimeoutMsg& other);
    virtual ~StreamTimeoutMsg();
    StreamTimeoutMsg& operator=(const StreamTimeoutMsg& other);
    virtual StreamTimeoutMsg *dup() const override {return new StreamTimeoutMsg(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual uint16_t getUniqueID() const;
    virtual void setUniqueID(uint16_t uniqueID);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const StreamTimeoutMsg& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, StreamTimeoutMsg& obj) {obj.parsimUnpack(b);}


namespace omnetpp {

template<> inline StreamTimeoutMsg *fromAnyPtr(any_ptr ptr) { return check_and_cast<StreamTimeoutMsg*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __STREAMTIMEOUT_M_H

