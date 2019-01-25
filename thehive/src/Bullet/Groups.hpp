#ifndef GROUPS_H
#define GROUPS_H

namespace gg{
    enum GROUP {
        GR_NONE = 0,
        GR_ALL = 1 << 0,
        GR_STATIC = 1 << 1,
        GR_AGENT = 1 << 2,
        GR_RAY = 1 << 3
        //GR_ALL =GR_STATIC|GR_AGENT|GR_RAY
    };
}

#endif
