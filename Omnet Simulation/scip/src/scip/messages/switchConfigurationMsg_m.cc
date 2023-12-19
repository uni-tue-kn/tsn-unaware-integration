//
// Generated file, do not edit! Created by opp_msgtool 6.0 from src/scip/messages/switchConfigurationMsg.msg.
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
#include "switchConfigurationMsg_m.h"

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

Register_Class(AddConfigurationMsg)

AddConfigurationMsg::AddConfigurationMsg(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

AddConfigurationMsg::AddConfigurationMsg(const AddConfigurationMsg& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

AddConfigurationMsg::~AddConfigurationMsg()
{
}

AddConfigurationMsg& AddConfigurationMsg::operator=(const AddConfigurationMsg& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void AddConfigurationMsg::copy(const AddConfigurationMsg& other)
{
    this->switchID = other.switchID;
    this->stream = other.stream;
    this->removeVlanTag = other.removeVlanTag;
    this->srcAddr = other.srcAddr;
    this->dstAddr = other.dstAddr;
    this->srcPort = other.srcPort;
    this->dstPort = other.dstPort;
    this->l4Proto = other.l4Proto;
    this->vlanID = other.vlanID;
    this->pcp = other.pcp;
    this->de = other.de;
}

void AddConfigurationMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->switchID);
    doParsimPacking(b,this->stream);
    doParsimPacking(b,this->removeVlanTag);
    doParsimPacking(b,this->srcAddr);
    doParsimPacking(b,this->dstAddr);
    doParsimPacking(b,this->srcPort);
    doParsimPacking(b,this->dstPort);
    doParsimPacking(b,this->l4Proto);
    doParsimPacking(b,this->vlanID);
    doParsimPacking(b,this->pcp);
    doParsimPacking(b,this->de);
}

void AddConfigurationMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->switchID);
    doParsimUnpacking(b,this->stream);
    doParsimUnpacking(b,this->removeVlanTag);
    doParsimUnpacking(b,this->srcAddr);
    doParsimUnpacking(b,this->dstAddr);
    doParsimUnpacking(b,this->srcPort);
    doParsimUnpacking(b,this->dstPort);
    doParsimUnpacking(b,this->l4Proto);
    doParsimUnpacking(b,this->vlanID);
    doParsimUnpacking(b,this->pcp);
    doParsimUnpacking(b,this->de);
}

uint8_t AddConfigurationMsg::getSwitchID() const
{
    return this->switchID;
}

void AddConfigurationMsg::setSwitchID(uint8_t switchID)
{
    this->switchID = switchID;
}

const char * AddConfigurationMsg::getStream() const
{
    return this->stream.c_str();
}

void AddConfigurationMsg::setStream(const char * stream)
{
    this->stream = stream;
}

bool AddConfigurationMsg::getRemoveVlanTag() const
{
    return this->removeVlanTag;
}

void AddConfigurationMsg::setRemoveVlanTag(bool removeVlanTag)
{
    this->removeVlanTag = removeVlanTag;
}

uint32_t AddConfigurationMsg::getSrcAddr() const
{
    return this->srcAddr;
}

void AddConfigurationMsg::setSrcAddr(uint32_t srcAddr)
{
    this->srcAddr = srcAddr;
}

uint32_t AddConfigurationMsg::getDstAddr() const
{
    return this->dstAddr;
}

void AddConfigurationMsg::setDstAddr(uint32_t dstAddr)
{
    this->dstAddr = dstAddr;
}

unsigned short AddConfigurationMsg::getSrcPort() const
{
    return this->srcPort;
}

void AddConfigurationMsg::setSrcPort(unsigned short srcPort)
{
    this->srcPort = srcPort;
}

unsigned short AddConfigurationMsg::getDstPort() const
{
    return this->dstPort;
}

void AddConfigurationMsg::setDstPort(unsigned short dstPort)
{
    this->dstPort = dstPort;
}

uint8_t AddConfigurationMsg::getL4Proto() const
{
    return this->l4Proto;
}

void AddConfigurationMsg::setL4Proto(uint8_t l4Proto)
{
    this->l4Proto = l4Proto;
}

uint16_t AddConfigurationMsg::getVlanID() const
{
    return this->vlanID;
}

void AddConfigurationMsg::setVlanID(uint16_t vlanID)
{
    this->vlanID = vlanID;
}

uint8_t AddConfigurationMsg::getPcp() const
{
    return this->pcp;
}

void AddConfigurationMsg::setPcp(uint8_t pcp)
{
    this->pcp = pcp;
}

bool AddConfigurationMsg::getDe() const
{
    return this->de;
}

void AddConfigurationMsg::setDe(bool de)
{
    this->de = de;
}

class AddConfigurationMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_switchID,
        FIELD_stream,
        FIELD_removeVlanTag,
        FIELD_srcAddr,
        FIELD_dstAddr,
        FIELD_srcPort,
        FIELD_dstPort,
        FIELD_l4Proto,
        FIELD_vlanID,
        FIELD_pcp,
        FIELD_de,
    };
  public:
    AddConfigurationMsgDescriptor();
    virtual ~AddConfigurationMsgDescriptor();

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

Register_ClassDescriptor(AddConfigurationMsgDescriptor)

AddConfigurationMsgDescriptor::AddConfigurationMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(scip::AddConfigurationMsg)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

AddConfigurationMsgDescriptor::~AddConfigurationMsgDescriptor()
{
    delete[] propertyNames;
}

bool AddConfigurationMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<AddConfigurationMsg *>(obj)!=nullptr;
}

const char **AddConfigurationMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *AddConfigurationMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int AddConfigurationMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 11+base->getFieldCount() : 11;
}

unsigned int AddConfigurationMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_switchID
        FD_ISEDITABLE,    // FIELD_stream
        FD_ISEDITABLE,    // FIELD_removeVlanTag
        FD_ISEDITABLE,    // FIELD_srcAddr
        FD_ISEDITABLE,    // FIELD_dstAddr
        FD_ISEDITABLE,    // FIELD_srcPort
        FD_ISEDITABLE,    // FIELD_dstPort
        FD_ISEDITABLE,    // FIELD_l4Proto
        FD_ISEDITABLE,    // FIELD_vlanID
        FD_ISEDITABLE,    // FIELD_pcp
        FD_ISEDITABLE,    // FIELD_de
    };
    return (field >= 0 && field < 11) ? fieldTypeFlags[field] : 0;
}

const char *AddConfigurationMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "switchID",
        "stream",
        "removeVlanTag",
        "srcAddr",
        "dstAddr",
        "srcPort",
        "dstPort",
        "l4Proto",
        "vlanID",
        "pcp",
        "de",
    };
    return (field >= 0 && field < 11) ? fieldNames[field] : nullptr;
}

int AddConfigurationMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "switchID") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "stream") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "removeVlanTag") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "srcAddr") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "dstAddr") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "srcPort") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "dstPort") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "l4Proto") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "vlanID") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "pcp") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "de") == 0) return baseIndex + 10;
    return base ? base->findField(fieldName) : -1;
}

const char *AddConfigurationMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",    // FIELD_switchID
        "string",    // FIELD_stream
        "bool",    // FIELD_removeVlanTag
        "uint32_t",    // FIELD_srcAddr
        "uint32_t",    // FIELD_dstAddr
        "unsigned short",    // FIELD_srcPort
        "unsigned short",    // FIELD_dstPort
        "uint8_t",    // FIELD_l4Proto
        "uint16_t",    // FIELD_vlanID
        "uint8_t",    // FIELD_pcp
        "bool",    // FIELD_de
    };
    return (field >= 0 && field < 11) ? fieldTypeStrings[field] : nullptr;
}

const char **AddConfigurationMsgDescriptor::getFieldPropertyNames(int field) const
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

const char *AddConfigurationMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int AddConfigurationMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    AddConfigurationMsg *pp = omnetpp::fromAnyPtr<AddConfigurationMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void AddConfigurationMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    AddConfigurationMsg *pp = omnetpp::fromAnyPtr<AddConfigurationMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'AddConfigurationMsg'", field);
    }
}

const char *AddConfigurationMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    AddConfigurationMsg *pp = omnetpp::fromAnyPtr<AddConfigurationMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string AddConfigurationMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    AddConfigurationMsg *pp = omnetpp::fromAnyPtr<AddConfigurationMsg>(object); (void)pp;
    switch (field) {
        case FIELD_switchID: return ulong2string(pp->getSwitchID());
        case FIELD_stream: return oppstring2string(pp->getStream());
        case FIELD_removeVlanTag: return bool2string(pp->getRemoveVlanTag());
        case FIELD_srcAddr: return ulong2string(pp->getSrcAddr());
        case FIELD_dstAddr: return ulong2string(pp->getDstAddr());
        case FIELD_srcPort: return ulong2string(pp->getSrcPort());
        case FIELD_dstPort: return ulong2string(pp->getDstPort());
        case FIELD_l4Proto: return ulong2string(pp->getL4Proto());
        case FIELD_vlanID: return ulong2string(pp->getVlanID());
        case FIELD_pcp: return ulong2string(pp->getPcp());
        case FIELD_de: return bool2string(pp->getDe());
        default: return "";
    }
}

void AddConfigurationMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    AddConfigurationMsg *pp = omnetpp::fromAnyPtr<AddConfigurationMsg>(object); (void)pp;
    switch (field) {
        case FIELD_switchID: pp->setSwitchID(string2ulong(value)); break;
        case FIELD_stream: pp->setStream((value)); break;
        case FIELD_removeVlanTag: pp->setRemoveVlanTag(string2bool(value)); break;
        case FIELD_srcAddr: pp->setSrcAddr(string2ulong(value)); break;
        case FIELD_dstAddr: pp->setDstAddr(string2ulong(value)); break;
        case FIELD_srcPort: pp->setSrcPort(string2ulong(value)); break;
        case FIELD_dstPort: pp->setDstPort(string2ulong(value)); break;
        case FIELD_l4Proto: pp->setL4Proto(string2ulong(value)); break;
        case FIELD_vlanID: pp->setVlanID(string2ulong(value)); break;
        case FIELD_pcp: pp->setPcp(string2ulong(value)); break;
        case FIELD_de: pp->setDe(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AddConfigurationMsg'", field);
    }
}

omnetpp::cValue AddConfigurationMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    AddConfigurationMsg *pp = omnetpp::fromAnyPtr<AddConfigurationMsg>(object); (void)pp;
    switch (field) {
        case FIELD_switchID: return (omnetpp::intval_t)(pp->getSwitchID());
        case FIELD_stream: return pp->getStream();
        case FIELD_removeVlanTag: return pp->getRemoveVlanTag();
        case FIELD_srcAddr: return (omnetpp::intval_t)(pp->getSrcAddr());
        case FIELD_dstAddr: return (omnetpp::intval_t)(pp->getDstAddr());
        case FIELD_srcPort: return (omnetpp::intval_t)(pp->getSrcPort());
        case FIELD_dstPort: return (omnetpp::intval_t)(pp->getDstPort());
        case FIELD_l4Proto: return (omnetpp::intval_t)(pp->getL4Proto());
        case FIELD_vlanID: return (omnetpp::intval_t)(pp->getVlanID());
        case FIELD_pcp: return (omnetpp::intval_t)(pp->getPcp());
        case FIELD_de: return pp->getDe();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'AddConfigurationMsg' as cValue -- field index out of range?", field);
    }
}

void AddConfigurationMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    AddConfigurationMsg *pp = omnetpp::fromAnyPtr<AddConfigurationMsg>(object); (void)pp;
    switch (field) {
        case FIELD_switchID: pp->setSwitchID(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_stream: pp->setStream(value.stringValue()); break;
        case FIELD_removeVlanTag: pp->setRemoveVlanTag(value.boolValue()); break;
        case FIELD_srcAddr: pp->setSrcAddr(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_dstAddr: pp->setDstAddr(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_srcPort: pp->setSrcPort(omnetpp::checked_int_cast<unsigned short>(value.intValue())); break;
        case FIELD_dstPort: pp->setDstPort(omnetpp::checked_int_cast<unsigned short>(value.intValue())); break;
        case FIELD_l4Proto: pp->setL4Proto(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_vlanID: pp->setVlanID(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_pcp: pp->setPcp(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_de: pp->setDe(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AddConfigurationMsg'", field);
    }
}

const char *AddConfigurationMsgDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr AddConfigurationMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    AddConfigurationMsg *pp = omnetpp::fromAnyPtr<AddConfigurationMsg>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void AddConfigurationMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    AddConfigurationMsg *pp = omnetpp::fromAnyPtr<AddConfigurationMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AddConfigurationMsg'", field);
    }
}

Register_Class(RemoveConfigurationMsg)

RemoveConfigurationMsg::RemoveConfigurationMsg(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

RemoveConfigurationMsg::RemoveConfigurationMsg(const RemoveConfigurationMsg& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

RemoveConfigurationMsg::~RemoveConfigurationMsg()
{
}

RemoveConfigurationMsg& RemoveConfigurationMsg::operator=(const RemoveConfigurationMsg& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void RemoveConfigurationMsg::copy(const RemoveConfigurationMsg& other)
{
    this->stream = other.stream;
}

void RemoveConfigurationMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->stream);
}

void RemoveConfigurationMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->stream);
}

const char * RemoveConfigurationMsg::getStream() const
{
    return this->stream.c_str();
}

void RemoveConfigurationMsg::setStream(const char * stream)
{
    this->stream = stream;
}

class RemoveConfigurationMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_stream,
    };
  public:
    RemoveConfigurationMsgDescriptor();
    virtual ~RemoveConfigurationMsgDescriptor();

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

Register_ClassDescriptor(RemoveConfigurationMsgDescriptor)

RemoveConfigurationMsgDescriptor::RemoveConfigurationMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(scip::RemoveConfigurationMsg)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

RemoveConfigurationMsgDescriptor::~RemoveConfigurationMsgDescriptor()
{
    delete[] propertyNames;
}

bool RemoveConfigurationMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RemoveConfigurationMsg *>(obj)!=nullptr;
}

const char **RemoveConfigurationMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RemoveConfigurationMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RemoveConfigurationMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int RemoveConfigurationMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_stream
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *RemoveConfigurationMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "stream",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int RemoveConfigurationMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "stream") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *RemoveConfigurationMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_stream
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **RemoveConfigurationMsgDescriptor::getFieldPropertyNames(int field) const
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

const char *RemoveConfigurationMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RemoveConfigurationMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RemoveConfigurationMsg *pp = omnetpp::fromAnyPtr<RemoveConfigurationMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RemoveConfigurationMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RemoveConfigurationMsg *pp = omnetpp::fromAnyPtr<RemoveConfigurationMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RemoveConfigurationMsg'", field);
    }
}

const char *RemoveConfigurationMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RemoveConfigurationMsg *pp = omnetpp::fromAnyPtr<RemoveConfigurationMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RemoveConfigurationMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RemoveConfigurationMsg *pp = omnetpp::fromAnyPtr<RemoveConfigurationMsg>(object); (void)pp;
    switch (field) {
        case FIELD_stream: return oppstring2string(pp->getStream());
        default: return "";
    }
}

void RemoveConfigurationMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RemoveConfigurationMsg *pp = omnetpp::fromAnyPtr<RemoveConfigurationMsg>(object); (void)pp;
    switch (field) {
        case FIELD_stream: pp->setStream((value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RemoveConfigurationMsg'", field);
    }
}

omnetpp::cValue RemoveConfigurationMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RemoveConfigurationMsg *pp = omnetpp::fromAnyPtr<RemoveConfigurationMsg>(object); (void)pp;
    switch (field) {
        case FIELD_stream: return pp->getStream();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RemoveConfigurationMsg' as cValue -- field index out of range?", field);
    }
}

void RemoveConfigurationMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RemoveConfigurationMsg *pp = omnetpp::fromAnyPtr<RemoveConfigurationMsg>(object); (void)pp;
    switch (field) {
        case FIELD_stream: pp->setStream(value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RemoveConfigurationMsg'", field);
    }
}

const char *RemoveConfigurationMsgDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr RemoveConfigurationMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RemoveConfigurationMsg *pp = omnetpp::fromAnyPtr<RemoveConfigurationMsg>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RemoveConfigurationMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RemoveConfigurationMsg *pp = omnetpp::fromAnyPtr<RemoveConfigurationMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RemoveConfigurationMsg'", field);
    }
}

}  // namespace scip

namespace omnetpp {

}  // namespace omnetpp

