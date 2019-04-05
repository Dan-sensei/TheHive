#ifndef _PARTICLE_H
#define _PARTICLE_H

#include <glm/glm.hpp>
#include <Util.hpp>

class Particle{

    public:
        Particle();
        Particle(const glm::vec3 &_Position, glm::vec3 _Velocity, const gg::Color &_Color, float _Life, float _Size);
        Particle(const Particle &orig);
        ~Particle();

        glm::vec3 Position;
        glm::vec3 Velocity;
        gg::Color Color;
        float Life, Size;
};

#endif
