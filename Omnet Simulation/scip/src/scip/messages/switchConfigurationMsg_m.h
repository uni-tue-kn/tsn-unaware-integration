//
// Generated file, do not edit! Created by opp_msgtool 6.0 from src/scip/messages/switchConfigurationMsg.msg.
//

#ifndef __SCIP_SWITCHCONFIGURATIONMSG_M_H
#define __SCIP_SWITCHCONFIGURATIONMSG_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// opp_msgtool version check
#define MSGC_VERSION 0x0600
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgtool: 'make clean' should help.
#endif


namespace scip {

class AddConfigurationMsg;
class RemoveConfigurationMsg;

}  // namespace scip


namespace scip {

/**
 * Class generated from <tt>src/scip/messages/switchConfigurationMsg.msg:2</tt> by opp_msgtool.
 * <pre>
 * message AddConfigurationMsg
 * {
 *     uint8_t switchID;
 *     string stream;
 *     bool removeVlanTag = false;
 *     uint32_t srcAddr;
 *     uint32_t dstAddr;
 *     unsigned short srcPort;
 *     unsigned short dstPort;
 *     uint8_t l4Proto;
 *     uint16_t vlanID;
 *     uint8_t pcp;
 *     bool de = false;
 * }
 * </pre>
 */
class AddConfigurationMsg : public ::omnetpp::cMessage
{
  protected:
    uint8_t switchID = 0;
    ::omnetpp::opp_string stream;
    bool removeVlanTag = false;
    uint32_t srcAddr = 0;
    uint32_t dstAddr = 0;
    unsigned short srcPort = 0;
    unsigned short dstPort = 0;
    uint8_t l4Proto = 0;
    uint16_t vlanID = 0;
    uint8_t pcp = 0;
    bool de = false;

  private:
    void copy(const AddConfigurationMsg& other);

  protected:
    bool operator==(const AddConfigurationMsg&) = delete;

  public:
    AddConfigurationMsg(const char *name=nullptr, short kind=0);
    AddConfigurationMsg(const AddConfigurationMsg& other);
    virtual ~AddConfigurationMsg();
    AddConfigurationMsg& operator=(const AddConfigurationMsg& other);
    virtual AddConfigurationMsg *dup() const override {return new AddConfigurationMsg(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual uint8_t getSwitchID() const;
    virtual void setSwitchID(uint8_t switchID);

    virtual const char * getStream() const;
    virtual void setStream(const char * stream);

    virtual bool getRemoveVlanTag() const;
    virtual void setRemoveVlanTag(bool removeVlanTag);

    virtual uint32_t getSrcAddr() const;
    virtual void setSrcAddr(uint32_t srcAddr);

    virtual uint32_t getDstAddr() const;
    virtual void setDstAddr(uint32_t dstAddr);

    virtual unsigned short getSrcPort() const;
    virtual void setSrcPort(unsigned short srcPort);

    virtual unsigned short getDstPort() const;
    virtual void setDstPort(unsigned short dstPort);

    virtual uint8_t getL4Proto() const;
    virtual void setL4Proto(uint8_t l4Proto);

    virtual uint16_t getVlanID() const;
    virtual void setVlanID(uint16_t vlanID);

    virtual uint8_t getPcp() const;
    virtual void setPcp(uint8_t pcp);

    virtual bool getDe() const;
    virtual void setDe(bool de);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const AddConfigurationMsg& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, AddConfigurationMsg& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>src/scip/messages/switchConfigurationMsg.msg:16</tt> by opp_msgtool.
 * <pre>
 * message RemoveConfigurationMsg
 * {
 *     string stream;
 * }
 * </pre>
 */
class RemoveConfigurationMsg : public ::omnetpp::cMessage
{
  protected:
    ::omnetpp::opp_string stream;

  private:
    void copy(const RemoveConfigurationMsg& other);

  protected:
    bool operator==(const RemoveConfigurationMsg&) = delete;

  public:
    RemoveConfigurationMsg(const char *name=nullptr, short kind=0);
    RemoveConfigurationMsg(const RemoveConfigurationMsg& other);
    virtual ~RemoveConfigurationMsg();
    RemoveConfigurationMsg& operator=(const RemoveConfigurationMsg& other);
    virtual RemoveConfigurationMsg *dup() const override {return new RemoveConfigurationMsg(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual const char * getStream() const;
    virtual void setStream(const char * stream);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RemoveConfigurationMsg& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RemoveConfigurationMsg& obj) {obj.parsimUnpack(b);}


}  // namespace scip


namespace omnetpp {

template<> inline scip::AddConfigurationMsg *fromAnyPtr(any_ptr ptr) { return check_and_cast<scip::AddConfigurationMsg*>(ptr.get<cObject>()); }
template<> inline scip::RemoveConfigurationMsg *fromAnyPtr(any_ptr ptr) { return check_and_cast<scip::RemoveConfigurationMsg*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __SCIP_SWITCHCONFIGURATIONMSG_M_H
