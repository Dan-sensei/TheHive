#ifndef ZSTATICSPOTLIGHT_H
#define ZSTATICSPOTLIGHT_H

#include "TLuz.hpp"

class ZStaticSpotLight : public TLuz {
    friend class LightRoot;

    public:
        ZStaticSpotLight(const glm::vec3 &Position, const glm::vec3 &LightColor, uint8_t _ZONE);
        ZStaticSpotLight(const ZStaticSpotLight &orig);
        ~ZStaticSpotLight();



        void setDireccion(const glm::vec3& dir);
        inline glm::vec3 getDireccion(){ return direccion; };
        inline glm::vec3 getPosition(){ return position; };

        virtual void beginDraw();
        virtual void endDraw();

    private:
        glm::vec3 position;
        glm::vec3 direccion;
        uint8_t ZONE;
        bool ACTIVE;
};

#endif
