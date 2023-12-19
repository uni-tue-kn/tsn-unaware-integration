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

#ifndef SCIP_APPLICATIONS_SWITCHCONFIGURATOR_H_
#define SCIP_APPLICATIONS_SWITCHCONFIGURATOR_H_

#include <omnetpp.h>
#include "scip/applications/base/ISwitchConfigurator.h"
#include "scip/core/TSNStream.h"
#include <unordered_map>


using namespace scip;
using namespace omnetpp;

//namespace scip {

class SwitchConfigurator : public cSimpleModule, public ISwitchConfigurator {
public:
    SwitchConfigurator();
    virtual ~SwitchConfigurator();
    void writeConfig(StreamIDTuple* stream, CBMapping* mapping ,uint16_t uniqueID, std::string name) override;
    void removeConfig(std::string name);
protected:
    void initialize() override;
    // Mapping stream unique ID to switch config
    std::unordered_map<uint16_t, std::vector<int>> switchConfig;
    int numSwitches;

};

//} // end namespace scip

#endif /* SCIP_APPLICATIONS_SWITCHCONFIGURATOR_H_ */
