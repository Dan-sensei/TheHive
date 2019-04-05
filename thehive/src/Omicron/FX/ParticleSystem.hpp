#ifndef _PARTICLE_SYSTEM
#define _PARTICLE_SYSTEM

#include "Particle.hpp"
#include <vector>
#include <cstdint>
#include <stack>
#include <Omicron/Clock.hpp>
#include <Omicron/Shader.hpp>

class ParticleSystem {

    public:
        ParticleSystem();
        ParticleSystem(const ParticleSystem &orig) = delete;
        ~ParticleSystem();

        void Init(float MaxParticles);
        void Update();
        void Draw();
        uint16_t getFreePosition();

        void setGenerationTime(float TIME_SECONDS);
        void setTexture(const std::string &_Texture);

    private:

        void ParticleCreationHandler();

        std::vector<Particle> Particles;
        std::vector<float> GL_Position_Size_Buffer;
        std::vector<float> GL_Color_Buffer;
        std::stack<uint16_t> AvailablePositions;

        gg::Clock Timer;

        Shader* Particles_Shader;

        float Accumulator;
        float DELAY;
        unsigned int PARTICLE_SYSTEM;
        unsigned int VBO_SHAPE;
        unsigned int VBO_POS_SIZE;
        unsigned int VBO_COLORS;

        unsigned int Texture;

        uint16_t ActiveParticles;

};

#endif
