//
// Generated file, do not edit! Created by opp_msgtool 6.0 from src/scip/messages/streamReservation.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "streamReservation_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace scip {

Register_Class(TalkerGroupMsg)

TalkerGroupMsg::TalkerGroupMsg(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

TalkerGroupMsg::TalkerGroupMsg(const TalkerGroupMsg& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

TalkerGroupMsg::~TalkerGroupMsg()
{
}

TalkerGroupMsg& TalkerGroupMsg::operator=(const TalkerGroupMsg& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void TalkerGroupMsg::copy(const TalkerGroupMsg& other)
{
    this->macAdress = other.macAdress;
    this->uniqueID = other.uniqueID;
    this->streamRank = other.streamRank;
    this->sendAdress = other.sendAdress;
    this->interfaceName = other.interfaceName;
    this->srcAddr = other.srcAddr;
    this->dstAddr = other.dstAddr;
    this->srcPort = other.srcPort;
    this->dstPort = other.dstPort;
    this->l4Proto = other.l4Proto;
    this->interval = other.interval;
    this->maxFramesPerInterval = other.maxFramesPerInterval;
    this->maxFrameSize = other.maxFrameSize;
    this->transmissionSelection = other.transmissionSelection;
    this->numSeamlessTrees = other.numSeamlessTrees;
    this->maxLatency = other.maxLatency;
}

void TalkerGroupMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->macAdress);
    doParsimPacking(b,this->uniqueID);
    doParsimPacking(b,this->streamRank);
    doParsimPacking(b,this->sendAdress);
    doParsimPacking(b,this->interfaceName);
    doParsimPacking(b,this->srcAddr);
    doParsimPacking(b,this->dstAddr);
    doParsimPacking(b,this->srcPort);
    doParsimPacking(b,this->dstPort);
    doParsimPacking(b,this->l4Proto);
    doParsimPacking(b,this->interval);
    doParsimPacking(b,this->maxFramesPerInterval);
    doParsimPacking(b,this->maxFrameSize);
    doParsimPacking(b,this->transmissionSelection);
    doParsimPacking(b,this->numSeamlessTrees);
    doParsimPacking(b,this->maxLatency);
}

void TalkerGroupMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->macAdress);
    doParsimUnpacking(b,this->uniqueID);
    doParsimUnpacking(b,this->streamRank);
    doParsimUnpacking(b,this->sendAdress);
    doParsimUnpacking(b,this->interfaceName);
    doParsimUnpacking(b,this->srcAddr);
    doParsimUnpacking(b,this->dstAddr);
    doParsimUnpacking(b,this->srcPort);
    doParsimUnpacking(b,this->dstPort);
    doParsimUnpacking(b,this->l4Proto);
    doParsimUnpacking(b,this->interval);
    doParsimUnpacking(b,this->maxFramesPerInterval);
    doParsimUnpacking(b,this->maxFrameSize);
    doParsimUnpacking(b,this->transmissionSelection);
    doParsimUnpacking(b,this->numSeamlessTrees);
    doParsimUnpacking(b,this->maxLatency);
}

uint64_t TalkerGroupMsg::getMacAdress() const
{
    return this->macAdress;
}

void TalkerGroupMsg::setMacAdress(uint64_t macAdress)
{
    this->macAdress = macAdress;
}

uint16_t TalkerGroupMsg::getUniqueID() const
{
    return this->uniqueID;
}

void TalkerGroupMsg::setUniqueID(uint16_t uniqueID)
{
    this->uniqueID = uniqueID;
}

uint8_t TalkerGroupMsg::getStreamRank() const
{
    return this->streamRank;
}

void TalkerGroupMsg::setStreamRank(uint8_t streamRank)
{
    this->streamRank = streamRank;
}

uint64_t TalkerGroupMsg::getSendAdress() const
{
    return this->sendAdress;
}

void TalkerGroupMsg::setSendAdress(uint64_t sendAdress)
{
    this->sendAdress = sendAdress;
}

const char * TalkerGroupMsg::getInterfaceName() const
{
    return this->interfaceName.c_str();
}

void TalkerGroupMsg::setInterfaceName(const char * interfaceName)
{
    this->interfaceName = interfaceName;
}

uint32_t TalkerGroupMsg::getSrcAddr() const
{
    return this->srcAddr;
}

void TalkerGroupMsg::setSrcAddr(uint32_t srcAddr)
{
    this->srcAddr = srcAddr;
}

uint32_t TalkerGroupMsg::getDstAddr() const
{
    return this->dstAddr;
}

void TalkerGroupMsg::setDstAddr(uint32_t dstAddr)
{
    this->dstAddr = dstAddr;
}

unsigned short TalkerGroupMsg::getSrcPort() const
{
    return this->srcPort;
}

void TalkerGroupMsg::setSrcPort(unsigned short srcPort)
{
    this->srcPort = srcPort;
}

unsigned short TalkerGroupMsg::getDstPort() const
{
    return this->dstPort;
}

void TalkerGroupMsg::setDstPort(unsigned short dstPort)
{
    this->dstPort = dstPort;
}

uint8_t TalkerGroupMsg::getL4Proto() const
{
    return this->l4Proto;
}

void TalkerGroupMsg::setL4Proto(uint8_t l4Proto)
{
    this->l4Proto = l4Proto;
}

float TalkerGroupMsg::getInterval() const
{
    return this->interval;
}

void TalkerGroupMsg::setInterval(float interval)
{
    this->interval = interval;
}

uint16_t TalkerGroupMsg::getMaxFramesPerInterval() const
{
    return this->maxFramesPerInterval;
}

void TalkerGroupMsg::setMaxFramesPerInterval(uint16_t maxFramesPerInterval)
{
    this->maxFramesPerInterval = maxFramesPerInterval;
}

uint16_t TalkerGroupMsg::getMaxFrameSize() const
{
    return this->maxFrameSize;
}

void TalkerGroupMsg::setMaxFrameSize(uint16_t maxFrameSize)
{
    this->maxFrameSize = maxFrameSize;
}

uint8_t TalkerGroupMsg::getTransmissionSelection() const
{
    return this->transmissionSelection;
}

void TalkerGroupMsg::setTransmissionSelection(uint8_t transmissionSelection)
{
    this->transmissionSelection = transmissionSelection;
}

uint8_t TalkerGroupMsg::getNumSeamlessTrees() const
{
    return this->numSeamlessTrees;
}

void TalkerGroupMsg::setNumSeamlessTrees(uint8_t numSeamlessTrees)
{
    this->numSeamlessTrees = numSeamlessTrees;
}

uint32_t TalkerGroupMsg::getMaxLatency() const
{
    return this->maxLatency;
}

void TalkerGroupMsg::setMaxLatency(uint32_t maxLatency)
{
    this->maxLatency = maxLatency;
}

class TalkerGroupMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_macAdress,
        FIELD_uniqueID,
        FIELD_streamRank,
        FIELD_sendAdress,
        FIELD_interfaceName,
        FIELD_srcAddr,
        FIELD_dstAddr,
        FIELD_srcPort,
        FIELD_dstPort,
        FIELD_l4Proto,
        FIELD_interval,
        FIELD_maxFramesPerInterval,
        FIELD_maxFrameSize,
        FIELD_transmissionSelection,
        FIELD_numSeamlessTrees,
        FIELD_maxLatency,
    };
  public:
    TalkerGroupMsgDescriptor();
    virtual ~TalkerGroupMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(TalkerGroupMsgDescriptor)

TalkerGroupMsgDescriptor::TalkerGroupMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(scip::TalkerGroupMsg)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

TalkerGroupMsgDescriptor::~TalkerGroupMsgDescriptor()
{
    delete[] propertyNames;
}

bool TalkerGroupMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TalkerGroupMsg *>(obj)!=nullptr;
}

const char **TalkerGroupMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TalkerGroupMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TalkerGroupMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 16+base->getFieldCount() : 16;
}

unsigned int TalkerGroupMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_macAdress
        FD_ISEDITABLE,    // FIELD_uniqueID
        FD_ISEDITABLE,    // FIELD_streamRank
        FD_ISEDITABLE,    // FIELD_sendAdress
        FD_ISEDITABLE,    // FIELD_interfaceName
        FD_ISEDITABLE,    // FIELD_srcAddr
        FD_ISEDITABLE,    // FIELD_dstAddr
        FD_ISEDITABLE,    // FIELD_srcPort
        FD_ISEDITABLE,    // FIELD_dstPort
        FD_ISEDITABLE,    // FIELD_l4Proto
        FD_ISEDITABLE,    // FIELD_interval
        FD_ISEDITABLE,    // FIELD_maxFramesPerInterval
        FD_ISEDITABLE,    // FIELD_maxFrameSize
        FD_ISEDITABLE,    // FIELD_transmissionSelection
        FD_ISEDITABLE,    // FIELD_numSeamlessTrees
        FD_ISEDITABLE,    // FIELD_maxLatency
    };
    return (field >= 0 && field < 16) ? fieldTypeFlags[field] : 0;
}

const char *TalkerGroupMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "macAdress",
        "uniqueID",
        "streamRank",
        "sendAdress",
        "interfaceName",
        "srcAddr",
        "dstAddr",
        "srcPort",
        "dstPort",
        "l4Proto",
        "interval",
        "maxFramesPerInterval",
        "maxFrameSize",
        "transmissionSelection",
        "numSeamlessTrees",
        "maxLatency",
    };
    return (field >= 0 && field < 16) ? fieldNames[field] : nullptr;
}

int TalkerGroupMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "macAdress") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "uniqueID") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "streamRank") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "sendAdress") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "interfaceName") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "srcAddr") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "dstAddr") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "srcPort") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "dstPort") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "l4Proto") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "interval") == 0) return baseIndex + 10;
    if (strcmp(fieldName, "maxFramesPerInterval") == 0) return baseIndex + 11;
    if (strcmp(fieldName, "maxFrameSize") == 0) return baseIndex + 12;
    if (strcmp(fieldName, "transmissionSelection") == 0) return baseIndex + 13;
    if (strcmp(fieldName, "numSeamlessTrees") == 0) return baseIndex + 14;
    if (strcmp(fieldName, "maxLatency") == 0) return baseIndex + 15;
    return base ? base->findField(fieldName) : -1;
}

const char *TalkerGroupMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint64_t",    // FIELD_macAdress
        "uint16_t",    // FIELD_uniqueID
        "uint8_t",    // FIELD_streamRank
        "uint64_t",    // FIELD_sendAdress
        "string",    // FIELD_interfaceName
        "uint32_t",    // FIELD_srcAddr
        "uint32_t",    // FIELD_dstAddr
        "unsigned short",    // FIELD_srcPort
        "unsigned short",    // FIELD_dstPort
        "uint8_t",    // FIELD_l4Proto
        "float",    // FIELD_interval
        "uint16_t",    // FIELD_maxFramesPerInterval
        "uint16_t",    // FIELD_maxFrameSize
        "uint8_t",    // FIELD_transmissionSelection
        "uint8_t",    // FIELD_numSeamlessTrees
        "uint32_t",    // FIELD_maxLatency
    };
    return (field >= 0 && field < 16) ? fieldTypeStrings[field] : nullptr;
}

const char **TalkerGroupMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *TalkerGroupMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int TalkerGroupMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TalkerGroupMsg *pp = omnetpp::fromAnyPtr<TalkerGroupMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TalkerGroupMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TalkerGroupMsg *pp = omnetpp::fromAnyPtr<TalkerGroupMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TalkerGroupMsg'", field);
    }
}

const char *TalkerGroupMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TalkerGroupMsg *pp = omnetpp::fromAnyPtr<TalkerGroupMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TalkerGroupMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TalkerGroupMsg *pp = omnetpp::fromAnyPtr<TalkerGroupMsg>(object); (void)pp;
    switch (field) {
        case FIELD_macAdress: return uint642string(pp->getMacAdress());
        case FIELD_uniqueID: return ulong2string(pp->getUniqueID());
        case FIELD_streamRank: return ulong2string(pp->getStreamRank());
        case FIELD_sendAdress: return uint642string(pp->getSendAdress());
        case FIELD_interfaceName: return oppstring2string(pp->getInterfaceName());
        case FIELD_srcAddr: return ulong2string(pp->getSrcAddr());
        case FIELD_dstAddr: return ulong2string(pp->getDstAddr());
        case FIELD_srcPort: return ulong2string(pp->getSrcPort());
        case FIELD_dstPort: return ulong2string(pp->getDstPort());
        case FIELD_l4Proto: return ulong2string(pp->getL4Proto());
        case FIELD_interval: return double2string(pp->getInterval());
        case FIELD_maxFramesPerInterval: return ulong2string(pp->getMaxFramesPerInterval());
        case FIELD_maxFrameSize: return ulong2string(pp->getMaxFrameSize());
        case FIELD_transmissionSelection: return ulong2string(pp->getTransmissionSelection());
        case FIELD_numSeamlessTrees: return ulong2string(pp->getNumSeamlessTrees());
        case FIELD_maxLatency: return ulong2string(pp->getMaxLatency());
        default: return "";
    }
}

void TalkerGroupMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TalkerGroupMsg *pp = omnetpp::fromAnyPtr<TalkerGroupMsg>(object); (void)pp;
    switch (field) {
        case FIELD_macAdress: pp->setMacAdress(string2uint64(value)); break;
        case FIELD_uniqueID: pp->setUniqueID(string2ulong(value)); break;
        case FIELD_streamRank: pp->setStreamRank(string2ulong(value)); break;
        case FIELD_sendAdress: pp->setSendAdress(string2uint64(value)); break;
        case FIELD_interfaceName: pp->setInterfaceName((value)); break;
        case FIELD_srcAddr: pp->setSrcAddr(string2ulong(value)); break;
        case FIELD_dstAddr: pp->setDstAddr(string2ulong(value)); break;
        case FIELD_srcPort: pp->setSrcPort(string2ulong(value)); break;
        case FIELD_dstPort: pp->setDstPort(string2ulong(value)); break;
        case FIELD_l4Proto: pp->setL4Proto(string2ulong(value)); break;
        case FIELD_interval: pp->setInterval(string2double(value)); break;
        case FIELD_maxFramesPerInterval: pp->setMaxFramesPerInterval(string2ulong(value)); break;
        case FIELD_maxFrameSize: pp->setMaxFrameSize(string2ulong(value)); break;
        case FIELD_transmissionSelection: pp->setTransmissionSelection(string2ulong(value)); break;
        case FIELD_numSeamlessTrees: pp->setNumSeamlessTrees(string2ulong(value)); break;
        case FIELD_maxLatency: pp->setMaxLatency(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TalkerGroupMsg'", field);
    }
}

omnetpp::cValue TalkerGroupMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TalkerGroupMsg *pp = omnetpp::fromAnyPtr<TalkerGroupMsg>(object); (void)pp;
    switch (field) {
        case FIELD_macAdress: return (omnetpp::intval_t)(pp->getMacAdress());
        case FIELD_uniqueID: return (omnetpp::intval_t)(pp->getUniqueID());
        case FIELD_streamRank: return (omnetpp::intval_t)(pp->getStreamRank());
        case FIELD_sendAdress: return (omnetpp::intval_t)(pp->getSendAdress());
        case FIELD_interfaceName: return pp->getInterfaceName();
        case FIELD_srcAddr: return (omnetpp::intval_t)(pp->getSrcAddr());
        case FIELD_dstAddr: return (omnetpp::intval_t)(pp->getDstAddr());
        case FIELD_srcPort: return (omnetpp::intval_t)(pp->getSrcPort());
        case FIELD_dstPort: return (omnetpp::intval_t)(pp->getDstPort());
        case FIELD_l4Proto: return (omnetpp::intval_t)(pp->getL4Proto());
        case FIELD_interval: return (double)(pp->getInterval());
        case FIELD_maxFramesPerInterval: return (omnetpp::intval_t)(pp->getMaxFramesPerInterval());
        case FIELD_maxFrameSize: return (omnetpp::intval_t)(pp->getMaxFrameSize());
        case FIELD_transmissionSelection: return (omnetpp::intval_t)(pp->getTransmissionSelection());
        case FIELD_numSeamlessTrees: return (omnetpp::intval_t)(pp->getNumSeamlessTrees());
        case FIELD_maxLatency: return (omnetpp::intval_t)(pp->getMaxLatency());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TalkerGroupMsg' as cValue -- field index out of range?", field);
    }
}

void TalkerGroupMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TalkerGroupMsg *pp = omnetpp::fromAnyPtr<TalkerGroupMsg>(object); (void)pp;
    switch (field) {
        case FIELD_macAdress: pp->setMacAdress(omnetpp::checked_int_cast<uint64_t>(value.intValue())); break;
        case FIELD_uniqueID: pp->setUniqueID(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_streamRank: pp->setStreamRank(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_sendAdress: pp->setSendAdress(omnetpp::checked_int_cast<uint64_t>(value.intValue())); break;
        case FIELD_interfaceName: pp->setInterfaceName(value.stringValue()); break;
        case FIELD_srcAddr: pp->setSrcAddr(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_dstAddr: pp->setDstAddr(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_srcPort: pp->setSrcPort(omnetpp::checked_int_cast<unsigned short>(value.intValue())); break;
        case FIELD_dstPort: pp->setDstPort(omnetpp::checked_int_cast<unsigned short>(value.intValue())); break;
        case FIELD_l4Proto: pp->setL4Proto(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_interval: pp->setInterval(static_cast<float>(value.doubleValue())); break;
        case FIELD_maxFramesPerInterval: pp->setMaxFramesPerInterval(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_maxFrameSize: pp->setMaxFrameSize(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_transmissionSelection: pp->setTransmissionSelection(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_numSeamlessTrees: pp->setNumSeamlessTrees(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_maxLatency: pp->setMaxLatency(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TalkerGroupMsg'", field);
    }
}

const char *TalkerGroupMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr TalkerGroupMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TalkerGroupMsg *pp = omnetpp::fromAnyPtr<TalkerGroupMsg>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TalkerGroupMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TalkerGroupMsg *pp = omnetpp::fromAnyPtr<TalkerGroupMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TalkerGroupMsg'", field);
    }
}

Register_Class(ListenerGroupMsg)

ListenerGroupMsg::ListenerGroupMsg(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

ListenerGroupMsg::ListenerGroupMsg(const ListenerGroupMsg& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

ListenerGroupMsg::~ListenerGroupMsg()
{
}

ListenerGroupMsg& ListenerGroupMsg::operator=(const ListenerGroupMsg& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void ListenerGroupMsg::copy(const ListenerGroupMsg& other)
{
    this->macAdress = other.macAdress;
    this->uniqueID = other.uniqueID;
    this->interfaceName = other.interfaceName;
    this->recvAdress = other.recvAdress;
}

void ListenerGroupMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->macAdress);
    doParsimPacking(b,this->uniqueID);
    doParsimPacking(b,this->interfaceName);
    doParsimPacking(b,this->recvAdress);
}

void ListenerGroupMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->macAdress);
    doParsimUnpacking(b,this->uniqueID);
    doParsimUnpacking(b,this->interfaceName);
    doParsimUnpacking(b,this->recvAdress);
}

uint64_t ListenerGroupMsg::getMacAdress() const
{
    return this->macAdress;
}

void ListenerGroupMsg::setMacAdress(uint64_t macAdress)
{
    this->macAdress = macAdress;
}

uint16_t ListenerGroupMsg::getUniqueID() const
{
    return this->uniqueID;
}

void ListenerGroupMsg::setUniqueID(uint16_t uniqueID)
{
    this->uniqueID = uniqueID;
}

const char * ListenerGroupMsg::getInterfaceName() const
{
    return this->interfaceName.c_str();
}

void ListenerGroupMsg::setInterfaceName(const char * interfaceName)
{
    this->interfaceName = interfaceName;
}

uint64_t ListenerGroupMsg::getRecvAdress() const
{
    return this->recvAdress;
}

void ListenerGroupMsg::setRecvAdress(uint64_t recvAdress)
{
    this->recvAdress = recvAdress;
}

class ListenerGroupMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_macAdress,
        FIELD_uniqueID,
        FIELD_interfaceName,
        FIELD_recvAdress,
    };
  public:
    ListenerGroupMsgDescriptor();
    virtual ~ListenerGroupMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(ListenerGroupMsgDescriptor)

ListenerGroupMsgDescriptor::ListenerGroupMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(scip::ListenerGroupMsg)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

ListenerGroupMsgDescriptor::~ListenerGroupMsgDescriptor()
{
    delete[] propertyNames;
}

bool ListenerGroupMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ListenerGroupMsg *>(obj)!=nullptr;
}

const char **ListenerGroupMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ListenerGroupMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ListenerGroupMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int ListenerGroupMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_macAdress
        FD_ISEDITABLE,    // FIELD_uniqueID
        FD_ISEDITABLE,    // FIELD_interfaceName
        FD_ISEDITABLE,    // FIELD_recvAdress
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *ListenerGroupMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "macAdress",
        "uniqueID",
        "interfaceName",
        "recvAdress",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int ListenerGroupMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "macAdress") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "uniqueID") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "interfaceName") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "recvAdress") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *ListenerGroupMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint64_t",    // FIELD_macAdress
        "uint16_t",    // FIELD_uniqueID
        "string",    // FIELD_interfaceName
        "uint64_t",    // FIELD_recvAdress
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **ListenerGroupMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *ListenerGroupMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int ListenerGroupMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    ListenerGroupMsg *pp = omnetpp::fromAnyPtr<ListenerGroupMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void ListenerGroupMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    ListenerGroupMsg *pp = omnetpp::fromAnyPtr<ListenerGroupMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'ListenerGroupMsg'", field);
    }
}

const char *ListenerGroupMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    ListenerGroupMsg *pp = omnetpp::fromAnyPtr<ListenerGroupMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ListenerGroupMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    ListenerGroupMsg *pp = omnetpp::fromAnyPtr<ListenerGroupMsg>(object); (void)pp;
    switch (field) {
        case FIELD_macAdress: return uint642string(pp->getMacAdress());
        case FIELD_uniqueID: return ulong2string(pp->getUniqueID());
        case FIELD_interfaceName: return oppstring2string(pp->getInterfaceName());
        case FIELD_recvAdress: return uint642string(pp->getRecvAdress());
        default: return "";
    }
}

void ListenerGroupMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ListenerGroupMsg *pp = omnetpp::fromAnyPtr<ListenerGroupMsg>(object); (void)pp;
    switch (field) {
        case FIELD_macAdress: pp->setMacAdress(string2uint64(value)); break;
        case FIELD_uniqueID: pp->setUniqueID(string2ulong(value)); break;
        case FIELD_interfaceName: pp->setInterfaceName((value)); break;
        case FIELD_recvAdress: pp->setRecvAdress(string2uint64(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ListenerGroupMsg'", field);
    }
}

omnetpp::cValue ListenerGroupMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    ListenerGroupMsg *pp = omnetpp::fromAnyPtr<ListenerGroupMsg>(object); (void)pp;
    switch (field) {
        case FIELD_macAdress: return (omnetpp::intval_t)(pp->getMacAdress());
        case FIELD_uniqueID: return (omnetpp::intval_t)(pp->getUniqueID());
        case FIELD_interfaceName: return pp->getInterfaceName();
        case FIELD_recvAdress: return (omnetpp::intval_t)(pp->getRecvAdress());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'ListenerGroupMsg' as cValue -- field index out of range?", field);
    }
}

void ListenerGroupMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ListenerGroupMsg *pp = omnetpp::fromAnyPtr<ListenerGroupMsg>(object); (void)pp;
    switch (field) {
        case FIELD_macAdress: pp->setMacAdress(omnetpp::checked_int_cast<uint64_t>(value.intValue())); break;
        case FIELD_uniqueID: pp->setUniqueID(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_interfaceName: pp->setInterfaceName(value.stringValue()); break;
        case FIELD_recvAdress: pp->setRecvAdress(omnetpp::checked_int_cast<uint64_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ListenerGroupMsg'", field);
    }
}

const char *ListenerGroupMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr ListenerGroupMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    ListenerGroupMsg *pp = omnetpp::fromAnyPtr<ListenerGroupMsg>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ListenerGroupMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    ListenerGroupMsg *pp = omnetpp::fromAnyPtr<ListenerGroupMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ListenerGroupMsg'", field);
    }
}

Register_Class(StatusGroupMsg)

StatusGroupMsg::StatusGroupMsg(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

StatusGroupMsg::StatusGroupMsg(const StatusGroupMsg& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

StatusGroupMsg::~StatusGroupMsg()
{
}

StatusGroupMsg& StatusGroupMsg::operator=(const StatusGroupMsg& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void StatusGroupMsg::copy(const StatusGroupMsg& other)
{
    this->macAdress = other.macAdress;
    this->uniqueID = other.uniqueID;
    this->talkerStatus = other.talkerStatus;
    this->listenerStatus = other.listenerStatus;
    this->failureCode = other.failureCode;
    this->accumulatedLatency = other.accumulatedLatency;
    this->pcp = other.pcp;
    this->vlanID = other.vlanID;
}

void StatusGroupMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->macAdress);
    doParsimPacking(b,this->uniqueID);
    doParsimPacking(b,this->talkerStatus);
    doParsimPacking(b,this->listenerStatus);
    doParsimPacking(b,this->failureCode);
    doParsimPacking(b,this->accumulatedLatency);
    doParsimPacking(b,this->pcp);
    doParsimPacking(b,this->vlanID);
}

void StatusGroupMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->macAdress);
    doParsimUnpacking(b,this->uniqueID);
    doParsimUnpacking(b,this->talkerStatus);
    doParsimUnpacking(b,this->listenerStatus);
    doParsimUnpacking(b,this->failureCode);
    doParsimUnpacking(b,this->accumulatedLatency);
    doParsimUnpacking(b,this->pcp);
    doParsimUnpacking(b,this->vlanID);
}

uint64_t StatusGroupMsg::getMacAdress() const
{
    return this->macAdress;
}

void StatusGroupMsg::setMacAdress(uint64_t macAdress)
{
    this->macAdress = macAdress;
}

uint16_t StatusGroupMsg::getUniqueID() const
{
    return this->uniqueID;
}

void StatusGroupMsg::setUniqueID(uint16_t uniqueID)
{
    this->uniqueID = uniqueID;
}

uint8_t StatusGroupMsg::getTalkerStatus() const
{
    return this->talkerStatus;
}

void StatusGroupMsg::setTalkerStatus(uint8_t talkerStatus)
{
    this->talkerStatus = talkerStatus;
}

uint8_t StatusGroupMsg::getListenerStatus() const
{
    return this->listenerStatus;
}

void StatusGroupMsg::setListenerStatus(uint8_t listenerStatus)
{
    this->listenerStatus = listenerStatus;
}

uint8_t StatusGroupMsg::getFailureCode() const
{
    return this->failureCode;
}

void StatusGroupMsg::setFailureCode(uint8_t failureCode)
{
    this->failureCode = failureCode;
}

uint32_t StatusGroupMsg::getAccumulatedLatency() const
{
    return this->accumulatedLatency;
}

void StatusGroupMsg::setAccumulatedLatency(uint32_t accumulatedLatency)
{
    this->accumulatedLatency = accumulatedLatency;
}

uint8_t StatusGroupMsg::getPcp() const
{
    return this->pcp;
}

void StatusGroupMsg::setPcp(uint8_t pcp)
{
    this->pcp = pcp;
}

uint16_t StatusGroupMsg::getVlanID() const
{
    return this->vlanID;
}

void StatusGroupMsg::setVlanID(uint16_t vlanID)
{
    this->vlanID = vlanID;
}

class StatusGroupMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_macAdress,
        FIELD_uniqueID,
        FIELD_talkerStatus,
        FIELD_listenerStatus,
        FIELD_failureCode,
        FIELD_accumulatedLatency,
        FIELD_pcp,
        FIELD_vlanID,
    };
  public:
    StatusGroupMsgDescriptor();
    virtual ~StatusGroupMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(StatusGroupMsgDescriptor)

StatusGroupMsgDescriptor::StatusGroupMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(scip::StatusGroupMsg)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

StatusGroupMsgDescriptor::~StatusGroupMsgDescriptor()
{
    delete[] propertyNames;
}

bool StatusGroupMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<StatusGroupMsg *>(obj)!=nullptr;
}

const char **StatusGroupMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *StatusGroupMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int StatusGroupMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 8+base->getFieldCount() : 8;
}

unsigned int StatusGroupMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_macAdress
        FD_ISEDITABLE,    // FIELD_uniqueID
        FD_ISEDITABLE,    // FIELD_talkerStatus
        FD_ISEDITABLE,    // FIELD_listenerStatus
        FD_ISEDITABLE,    // FIELD_failureCode
        FD_ISEDITABLE,    // FIELD_accumulatedLatency
        FD_ISEDITABLE,    // FIELD_pcp
        FD_ISEDITABLE,    // FIELD_vlanID
    };
    return (field >= 0 && field < 8) ? fieldTypeFlags[field] : 0;
}

const char *StatusGroupMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "macAdress",
        "uniqueID",
        "talkerStatus",
        "listenerStatus",
        "failureCode",
        "accumulatedLatency",
        "pcp",
        "vlanID",
    };
    return (field >= 0 && field < 8) ? fieldNames[field] : nullptr;
}

int StatusGroupMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "macAdress") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "uniqueID") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "talkerStatus") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "listenerStatus") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "failureCode") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "accumulatedLatency") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "pcp") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "vlanID") == 0) return baseIndex + 7;
    return base ? base->findField(fieldName) : -1;
}

const char *StatusGroupMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint64_t",    // FIELD_macAdress
        "uint16_t",    // FIELD_uniqueID
        "uint8_t",    // FIELD_talkerStatus
        "uint8_t",    // FIELD_listenerStatus
        "uint8_t",    // FIELD_failureCode
        "uint32_t",    // FIELD_accumulatedLatency
        "uint8_t",    // FIELD_pcp
        "uint16_t",    // FIELD_vlanID
    };
    return (field >= 0 && field < 8) ? fieldTypeStrings[field] : nullptr;
}

const char **StatusGroupMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *StatusGroupMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int StatusGroupMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    StatusGroupMsg *pp = omnetpp::fromAnyPtr<StatusGroupMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void StatusGroupMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    StatusGroupMsg *pp = omnetpp::fromAnyPtr<StatusGroupMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'StatusGroupMsg'", field);
    }
}

const char *StatusGroupMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    StatusGroupMsg *pp = omnetpp::fromAnyPtr<StatusGroupMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string StatusGroupMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    StatusGroupMsg *pp = omnetpp::fromAnyPtr<StatusGroupMsg>(object); (void)pp;
    switch (field) {
        case FIELD_macAdress: return uint642string(pp->getMacAdress());
        case FIELD_uniqueID: return ulong2string(pp->getUniqueID());
        case FIELD_talkerStatus: return ulong2string(pp->getTalkerStatus());
        case FIELD_listenerStatus: return ulong2string(pp->getListenerStatus());
        case FIELD_failureCode: return ulong2string(pp->getFailureCode());
        case FIELD_accumulatedLatency: return ulong2string(pp->getAccumulatedLatency());
        case FIELD_pcp: return ulong2string(pp->getPcp());
        case FIELD_vlanID: return ulong2string(pp->getVlanID());
        default: return "";
    }
}

void StatusGroupMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    StatusGroupMsg *pp = omnetpp::fromAnyPtr<StatusGroupMsg>(object); (void)pp;
    switch (field) {
        case FIELD_macAdress: pp->setMacAdress(string2uint64(value)); break;
        case FIELD_uniqueID: pp->setUniqueID(string2ulong(value)); break;
        case FIELD_talkerStatus: pp->setTalkerStatus(string2ulong(value)); break;
        case FIELD_listenerStatus: pp->setListenerStatus(string2ulong(value)); break;
        case FIELD_failureCode: pp->setFailureCode(string2ulong(value)); break;
        case FIELD_accumulatedLatency: pp->setAccumulatedLatency(string2ulong(value)); break;
        case FIELD_pcp: pp->setPcp(string2ulong(value)); break;
        case FIELD_vlanID: pp->setVlanID(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'StatusGroupMsg'", field);
    }
}

omnetpp::cValue StatusGroupMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    StatusGroupMsg *pp = omnetpp::fromAnyPtr<StatusGroupMsg>(object); (void)pp;
    switch (field) {
        case FIELD_macAdress: return (omnetpp::intval_t)(pp->getMacAdress());
        case FIELD_uniqueID: return (omnetpp::intval_t)(pp->getUniqueID());
        case FIELD_talkerStatus: return (omnetpp::intval_t)(pp->getTalkerStatus());
        case FIELD_listenerStatus: return (omnetpp::intval_t)(pp->getListenerStatus());
        case FIELD_failureCode: return (omnetpp::intval_t)(pp->getFailureCode());
        case FIELD_accumulatedLatency: return (omnetpp::intval_t)(pp->getAccumulatedLatency());
        case FIELD_pcp: return (omnetpp::intval_t)(pp->getPcp());
        case FIELD_vlanID: return (omnetpp::intval_t)(pp->getVlanID());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'StatusGroupMsg' as cValue -- field index out of range?", field);
    }
}

void StatusGroupMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    StatusGroupMsg *pp = omnetpp::fromAnyPtr<StatusGroupMsg>(object); (void)pp;
    switch (field) {
        case FIELD_macAdress: pp->setMacAdress(omnetpp::checked_int_cast<uint64_t>(value.intValue())); break;
        case FIELD_uniqueID: pp->setUniqueID(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_talkerStatus: pp->setTalkerStatus(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_listenerStatus: pp->setListenerStatus(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_failureCode: pp->setFailureCode(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_accumulatedLatency: pp->setAccumulatedLatency(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_pcp: pp->setPcp(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_vlanID: pp->setVlanID(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'StatusGroupMsg'", field);
    }
}

const char *StatusGroupMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr StatusGroupMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    StatusGroupMsg *pp = omnetpp::fromAnyPtr<StatusGroupMsg>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void StatusGroupMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    StatusGroupMsg *pp = omnetpp::fromAnyPtr<StatusGroupMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'StatusGroupMsg'", field);
    }
}

}  // namespace scip

namespace omnetpp {

}  // namespace omnetpp

