#ifndef LIGHTROOT_H
#define LIGHTROOT_H

#include <Omicron/CORE/ZNode.hpp>
#include <Omicron/LIGHTS/ZStaticPointLight.hpp>
#include <Omicron/LIGHTS/ZStaticSpotLight.hpp>
#include <Omicron/CORE/Leaf.hpp>
#include <vector>

class Omicron;


class LightRoot : public ZNode {
    friend class Omicron;
    public:
        LightRoot(ZNode* P);
        LightRoot(const LightRoot &orig);
        ~LightRoot();

        virtual void draw();
        virtual bool isLeaf();

        void setOVERRIDE(uint8_t ZONE);
        ZStaticSpotLight* emplace_SpotLight(const glm::vec3 &MVP, const glm::vec3 &Color, uint8_t ZONE);
        ZStaticPointLight* emplace_PointLight(const glm::vec3 &MVP, const glm::vec3 &Color, uint8_t ZONE);

    private:
        std::vector<ZStaticSpotLight> SPOT_LIGHTS;
        std::vector<ZStaticPointLight> POINT_LIGHTS;
        Omicron* Engine;
        static glm::vec3* CameraPosition;
};

#endif
