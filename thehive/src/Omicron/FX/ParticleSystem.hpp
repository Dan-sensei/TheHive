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
        void setTexture(unsigned int _Texture);
        void setParticleLifeTime(float Life);
        void setPosition(const glm::vec3 &_Position);
        void setSize(const glm::vec3 &_Size);

        virtual void beginDraw();
        virtual void endDraw();

        float Accumulator;

        float DELAY;
        float ParticleLifeTime;
        uint8_t MAXALPHA;


    private:

        void ParticleCreationHandler();
        uint16_t getFreePosition();

        std::vector<Particle> Particles;
        std::vector<float> GL_Position_Size_Buffer;
        std::vector<GLubyte> GL_Color_Buffer;

        gg::Clock Timer;

        glm::vec3 Position;
        glm::vec3 Size;

        Shader* Particles_Shader;


        unsigned int PARTICLE_SYSTEM;
        unsigned int VBO_SHAPE;
        unsigned int VBO_POS_SIZE;
        unsigned int VBO_COLORS;

        unsigned int Texture;

        uint16_t ActiveParticles;
        uint16_t LastAvailablePosition;

        void (ParticleSystem::*CurrentUpdate)();

};

#endif
