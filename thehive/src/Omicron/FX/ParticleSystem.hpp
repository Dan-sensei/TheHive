#ifndef _PARTICLE_SYSTEM
#define _PARTICLE_SYSTEM

#include "Particle.hpp"
#include <vector>
#include <cstdint>
#include <stack>
#include <Omicron/Clock.hpp>
#include <Omicron/Shader.hpp>
#include <Omicron/CORE/TEntidad.hpp>
#include "Particle_System_DATA.hpp"

class ParticleSystem : public TEntidad {

    public:
        ParticleSystem();
        ParticleSystem(const ParticleSystem &orig) = delete;
        ~ParticleSystem();

        void Init(float MaxParticles);
        void ResetTimerAndToggleUpdate();
        void UpdateAndDraw();
        void Update();
        void Draw();

        void setGenerationTime(float TIME_SECONDS);
        void setTexture(const std::string &_Texture);

        virtual void beginDraw();
        virtual void endDraw();

    private:

        void ParticleCreationHandler();
        uint16_t getFreePosition();

        std::vector<Particle> Particles;
        std::vector<float> GL_Position_Size_Buffer;
        std::vector<float> GL_Color_Buffer;
        uint16_t LastAvailablePosition;

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

        void (ParticleSystem::*CurrentUpdate)();

};

#endif
