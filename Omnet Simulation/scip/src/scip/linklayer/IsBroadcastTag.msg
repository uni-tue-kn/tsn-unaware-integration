//
// Copyright (C) 2020 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

import inet.common.INETDefs;
import inet.common.TagBase;

namespace scip;

class IsBroadcastTag extends inet::TagBase
{
    bool isBoradcast = true; // a locally unique (network node) identifier that determines the interface registered in the ~InterfaceTable
}
