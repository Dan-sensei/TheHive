#ifndef _CGRANADE_ONE_H
#define _CGRANADE_ONE_H

#include "CGranade.hpp"

#include "ComponentArch/Message.hpp"
#include <EventSystem/TData.hpp>
#include "Factory.hpp"

class CGranade1 : public CGranade {
    public:
        CGranade1();
        CGranade1(const CGranade1 &orig) = delete;
        virtual ~CGranade1();
        virtual void explosion();

    private:
        float damage;
};

#endif
