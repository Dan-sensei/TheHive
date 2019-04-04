#ifndef _PARTICLE_H
#define _PARTICLE_H

#include <glm/glm.hpp>
#include <Util.hpp>

class Particle{

    public:
        Particle();
        Particle(const glm::vec3 &_Position, const gg::Color &_Color, float _Velocity, float _Life);
        Particle(const Particle &orig);
        ~Particle();

    private:
        glm::vec3 Position;
        gg::Color Color;
        float Velocity;
        float Life;
};

#endif