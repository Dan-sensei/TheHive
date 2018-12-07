#ifndef _CGRANADE1_H
#define _CGRANADE1_H

#include "CGranade.hpp"




class CGranade1 : public CGranade {
    public:
        CGranade1();
        CGranade1(const CGranade &orig) = delete;
        virtual ~CGranade1();
        virtual void explosion();


    private:
        float damage;

};

#endif
