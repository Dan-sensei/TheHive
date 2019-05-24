#ifndef ZSTATICPOINTLIGHT_H
#define ZSTATICPOINTLIGHT_H

#include "TLuz.hpp"

class ZStaticPointLight : public TLuz{
    friend class LightRoot;

    public:
        ZStaticPointLight(const glm::vec3 &Position, const glm::vec3 &LightColor, uint8_t _ZONE);
        ZStaticPointLight(const ZStaticPointLight &orig);
        ~ZStaticPointLight();

        inline glm::vec3 getPosition(){ return position; };

        virtual void beginDraw();
        virtual void endDraw();

    private:
        glm::vec3 position;
        uint8_t ZONE;
        bool ACTIVE;
};

#endif
