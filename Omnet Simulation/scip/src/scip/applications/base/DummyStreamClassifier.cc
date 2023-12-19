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

#include "DummyStreamClassifier.h"

Define_Module(DummyStreamClassifier);

DummyStreamClassifier::DummyStreamClassifier() {
    // TODO Auto-generated constructor stub

}

DummyStreamClassifier::~DummyStreamClassifier() {
    // TODO Auto-generated destructor stub
}



// TODO: this probably should only be passed the IEEE8021Qcc class
// Furthermore it should be obvious, that the StreamDbEntry is altered in thsi call!
void DummyStreamClassifier::classifyStream(StreamIDTuple* stream, StreamDbEntry* entry) {
    entry->streamInfo->setTrafficSpecification({
        0.0,
        0,
        0,
        0
    });

    entry->streamInfo->setUserToNetworkRequirements({
        0,
        0
    });

    entry->state = classification_successfull;
}

