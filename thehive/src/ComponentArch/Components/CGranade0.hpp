#ifndef _CGRANADE0_H
#define _CGRANADE0_H

#include "CGranade.hpp"




class CGranade0 : public CGranade {
    public:
        CGranade0();
        CGranade0(const CGranade &orig) = delete;
        virtual ~CGranade0();
        virtual void explosion();

    private:
        float damage;


};

#endif
