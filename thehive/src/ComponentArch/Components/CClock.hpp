#ifndef _CCLOCK_H
#define _CCLOCK_H

#include <ComponentArch/IComponent.hpp>         // [OBLIGATORIO]
#include <chrono>

class CClock : public IComponent {
    public:
        CClock();
        CClock(const CClock &orig) = delete;
        virtual ~CClock();

        // Functions of IComponent
        virtual void Init();

        // Funciones propias
        bool startChrono(float);
        bool setEndTime(float);
        float getActualTime();
        bool hasEnded();
        void restart();

    private:

        bool initialized;
        bool limitReached;
        float msEnd;
        std::chrono::high_resolution_clock::time_point begin;

};

#endif
