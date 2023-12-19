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

package scip.core;


simple SCIPInterface {
    parameters:
        int switchID;
        //string streamIdentifierModule = default("^.bridging.streamIdentifier.identifier");
        string streamEncoderModule = default("^.bridging.streamCoder.encoder");
        string streamDecoderModule = default("^.bridging.streamCoder.decoder");
        @class(SCIPInterface);
    @display("i=block/arrival");
    gates:
        input confMessageIn;
}