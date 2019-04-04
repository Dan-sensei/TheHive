#include "ParticleSystem.hpp"

#include <GL/glew.h>

ParticleSystem::ParticleSystem(float MaxParticles){

    Particles.reserve(MaxParticles);
    glGenVertexArrays(1, &PARTICLE_SYSTEM);

    static const GLfloat QUAD[] = {
       -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
       -0.5f,  0.5f, 0.0f,
        0.5f,  0.5f, 0.0f,
    };
    glGenBuffers(1, &VBO_SHAPE);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_SHAPE);
    glBufferData(GL_ARRAY_BUFFER, sizeof(QUAD), QUAD, GL_STATIC_DRAW);

    glGenBuffers(1, &VBO_POS_SIZE);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_POS_SIZE);
    glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);

    glGenBuffers(1, &VBO_COLORS);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_COLORS);
    glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);

    glBindVertexArray(PARTICLE_SYSTEM);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        glVertexAttribFormat(0, 3, GL_FLOAT, false, 0);
        glVertexAttribFormat(1, 4, GL_FLOAT, false, 12);
        glVertexAttribFormat(2, 4, GL_UNSIGNED_BYTE, true, 0);

        glVertexAttribBinding(0, 0);
        glVertexAttribBinding(1, 1);
        glVertexAttribBinding(2, 2);

        glBindVertexBuffer(0, VBO_SHAPE, 0, 12);
        glBindVertexBuffer(1, VBO_POS_SIZE, 0, 16);
        glBindVertexBuffer(2, VBO_COLORS, 0, 16);
    glBindVertexArray(0);
}

ParticleSystem::~ParticleSystem(){
    glDeleteBuffers(1, &VBO_SHAPE);
    glDeleteBuffers(1, &VBO_POS_SIZE);
    glDeleteBuffers(1, &VBO_COLORS);
    glDeleteVertexArrays(1, &PARTICLE_SYSTEM);
}

void ParticleSystem::Update(){
    ActiveParticles = 0;

    auto CurrentParticle = Particles.begin();

    while(CurrentParticle != Particles.end()){

        

        ++CurrentParticle;
        ++ActiveParticles;
    }
}

void ParticleSystem::Draw(){
    glVertexAttribDivisor(0, 0);
    glVertexAttribDivisor(1, 1);
    glVertexAttribDivisor(2, 1);
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, ActiveParticles);
}