#ifndef _PARTICLE_SYSTEM_PALETTE_H
#define _PARTICLE_SYSTEM_PALETTE_H

#include <string>
#include <glm/glm.hpp>
#include <cstdint>

struct ParticleSystem_Data{
    ParticleSystem_Data()
    :Texture(""),SpawnTime(0),MaxParticles(0)
    {}

    std::string Texture;
    float SpawnTime;
    uint16_t MaxParticles;
};

#endif
