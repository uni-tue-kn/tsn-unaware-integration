/*
 * StreamClassifier.h
 *
 *  Created on: May 22, 2022
 *      Author: moritz
 */

//#include "inet/linklayer/ethernet/EtherFrame_m.h"
//#include "inet/common/packet/Packet.h"
#include <omnetpp.h>

#include "scip/applications/StreamDatabase.h"
#include "scip/core/TSNStream.h"
#include "scip/applications/base/IStreamClassifier.h"

using namespace omnetpp;
using namespace scip;
//using namespace inet;
//using namespace nesting;

//namespace scip {

class StreamClassifier : public cSimpleModule, public IStreamClassifier
{

protected:
    virtual void initialize() override;
public:
    void classifyStream(StreamIDTuple* stream, StreamDbEntry* entry) override;
private:
    void parseXML(StreamIDTuple* stream, StreamDbEntry* entry);
    bool doRhebo;
};
//} // namespace SCIPFramework

