#ifndef _CGRANADE2_H
#define _CGRANADE2_H

#include "CGranade.hpp"




class CGranade2 : public CGranade {
    public:
        CGranade2();
        CGranade2(const CGranade &orig) = delete;
        virtual ~CGranade2();
        virtual void explosion();


    private:


};

#endif
