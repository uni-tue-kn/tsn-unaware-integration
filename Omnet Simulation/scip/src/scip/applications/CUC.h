/*
 * CUC.h
 *
 *  Created on: May 22, 2022
 *      Author: moritz
 */

#ifndef SCIPFRAMEWORK_NETWORKLAYER_CUC_H_
#define SCIPFRAMEWORK_NETWORKLAYER_CUC_H_

//#include "inet/linklayer/ethernet/EtherFrame_m.h"
//#include "inet/common/packet/Packet.h"
#include <omnetpp.h>

#include "base/ICUC.h"
//#include "scip/applications/StreamDatabase.h"
#include "scip/core/TSNStream.h"
#include "scip/applications/StreamLifecycleManager.h"


using namespace omnetpp;
using namespace scip;
//using namespace inet;
//using namespace nesting;

//namespace scip {

struct cncStreamInfo {
    uint16_t uniqueID;
    StreamIDTuple streamIdentifier;
};

class CUC : public cSimpleModule, public ICUC
{
    protected:
        virtual void handleMessage(cMessage* msg) override;
        StreamLifecycleManager* streamManager;
        virtual void initialize() override;
    public:
        void registerStream(StreamIDTuple* streamIdentifier, IEEE8021QccStreamInfo* streamInfo);
    private:
        // Used to lookup stream ID and use same index to access talkers
        // TODO: better data structure for lookup
        std::list<cncStreamInfo > streams;

};
//} // namespace SCIPFramework

#endif /* SCIPFRAMEWORK_NETWORKLAYER_CUC_H_ */
