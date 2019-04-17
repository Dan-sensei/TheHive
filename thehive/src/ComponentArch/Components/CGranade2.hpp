#ifndef _CGRANADE_TWO_H
#define _CGRANADE_TWO_H

#include "CGranade.hpp"

#include "ComponentArch/Message.hpp"
#include <EventSystem/TData.hpp>
#include "Factory.hpp"

class CGranade2 : public CGranade {
    public:
        CGranade2();
        CGranade2(const CGranade2 &orig) = delete;
        virtual ~CGranade2();
        virtual void explosion();

    private:

};

#endif
