#ifndef _CGRANADE_ZERO_H
#define _CGRANADE_ZERO_H

#include "CGranade.hpp"

#include "ComponentArch/Message.hpp"
#include <EventSystem/TData.hpp>

#include "Factory.hpp"

class CGranade0 : public CGranade {
    public:
        CGranade0();
        CGranade0(const CGranade0 &orig) = delete;
        virtual ~CGranade0();
        virtual void explosion();

    private:
        float damage;
};

#endif
