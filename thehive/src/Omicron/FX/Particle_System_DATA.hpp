#ifndef _PARTICLE_SYSTEM_PALETTE_H
#define _PARTICLE_SYSTEM_PALETTE_H

#include <string>
#include <glm/glm.hpp>
#include <cstdint>

struct ParticleSystem_Data{
    ParticleSystem_Data()
    :Position(glm::vec3()), Size(glm::vec3()), Texture(0), SpawnTime(0),MaxParticles(0)
    {}

    glm::vec3 Position;
    glm::vec3 Size;
    unsigned int Texture;
    float SpawnTime;
    float ParticleLifeTime;
    uint16_t MaxParticles;
};

#endif
