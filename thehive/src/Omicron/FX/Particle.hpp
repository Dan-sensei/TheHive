#ifndef _PARTICLE_H
#define _PARTICLE_H

#include <glm/glm.hpp>
#include <Util.hpp>

class Particle{

    public:
        Particle();
        Particle(const glm::vec3 &_Position, glm::vec3 _Velocity, uint8_t _R, uint8_t _G, uint8_t _B, uint8_t _A, float _Life, float _Size);
        Particle(const Particle &orig);
        ~Particle();

        glm::vec3 Position;
        glm::vec3 Velocity;
        uint8_t R,G,B,A;
        float Life, Size;
};

#endif
