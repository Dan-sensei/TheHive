#ifndef _PARTICLE_SYSTEM
#define _PARTICLE_SYSTEM

#include "Particle.hpp"
#include <vector>
#include <cstdint>
#include <stack>

class ParticleSystem{

    public:
        ParticleSystem(float MaxParticles);
        ParticleSystem(const ParticleSystem &orig) = delete;
        ~ParticleSystem();

        void Update();
        void Draw();

    private:

        std::vector<Particle> Particles;
        std::stack<uint16_t> AvailablePositions;

        unsigned int PARTICLE_SYSTEM;
        unsigned int VBO_SHAPE;
        unsigned int VBO_POS_SIZE;
        unsigned int VBO_COLORS;

        uint16_t ActiveParticles;

};

#endif