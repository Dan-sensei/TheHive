#ifndef FADE_H
#define FADE_H

#include <Singleton.hpp>
#include "Clock.hpp"
#include "Shader.hpp"

class Fade{
    friend class Singleton<Fade>;
    public:
        Fade();
        Fade(const Fade &orig);
        ~Fade();

        void setFadeIn(float TIME = 2);
        void setFadeOut(float TIME = 2);

        bool Draw();

    private:

        float UpdateFadeIn();
        float UpdateFadeOut();

        float (Fade::*UPD)();

        gg::Clock clock;
        Shader* SHADER;

        double Accumulator;
        float TARGET_TIME;
        unsigned int QUAD;
        unsigned int VBO;
};

#endif
