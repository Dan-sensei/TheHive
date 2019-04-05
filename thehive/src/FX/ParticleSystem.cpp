#include "ParticleSystem.hpp"

#include <GL/glew.h>
#include <Util.hpp>
#include <Singleton.hpp>
#include <Omicron/AssetManager.hpp>
#include <ShaderUniformMapping.hpp>
#include <iostream>

ParticleSystem::ParticleSystem()
:DELAY(0), Accumulator(0)
{



    Particles_Shader = Singleton<AssetManager>::Instance()->getShader("Particles");
}

ParticleSystem::~ParticleSystem(){
    glDeleteBuffers(1, &VBO_SHAPE);
    glDeleteBuffers(1, &VBO_POS_SIZE);
    glDeleteBuffers(1, &VBO_COLORS);
    glDeleteVertexArrays(1, &PARTICLE_SYSTEM);
}

void ParticleSystem::Init(float MaxParticles){
    Particles.reserve(MaxParticles);
    Particles.resize(MaxParticles);
    GL_Position_Size_Buffer.reserve(MaxParticles * 4);
    GL_Position_Size_Buffer.resize(MaxParticles * 4);
    GL_Color_Buffer.reserve(MaxParticles * 4);
    GL_Color_Buffer.resize(MaxParticles * 4);

    AvailablePositions.push(0);

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
    glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), nullptr, GL_STREAM_DRAW);

    glGenBuffers(1, &VBO_COLORS);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_COLORS);
    glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLubyte), nullptr, GL_STREAM_DRAW);

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

void ParticleSystem::setGenerationTime(float TIME_SECONDS){
    DELAY = TIME_SECONDS;
}

void ParticleSystem::setTexture(const std::string &_Texture){
    Texture = Singleton<AssetManager>::Instance()->getTexture(_Texture);
}


void ParticleSystem::Update(){

    ParticleCreationHandler();

    ActiveParticles = 0;

    uint16_t i = Particles.size();
    float ElapsedTime = Timer.Restart().Seconds();
    while(i--){

        Particle &CurrentParticle = Particles[i];
        CurrentParticle.Life -= ElapsedTime;
        if(CurrentParticle.Life > 0){
            CurrentParticle.Position += CurrentParticle.Velocity;
            GL_Position_Size_Buffer[4*ActiveParticles+0] = CurrentParticle.Position.x;
            GL_Position_Size_Buffer[4*ActiveParticles+1] = CurrentParticle.Position.y;
            GL_Position_Size_Buffer[4*ActiveParticles+2] = CurrentParticle.Position.z;

            GL_Position_Size_Buffer[4*ActiveParticles+3] = CurrentParticle.Size;

            GL_Color_Buffer[4*ActiveParticles+0] = CurrentParticle.Color.R;
            GL_Color_Buffer[4*ActiveParticles+1] = CurrentParticle.Color.G;
            GL_Color_Buffer[4*ActiveParticles+2] = CurrentParticle.Color.B;
            GL_Color_Buffer[4*ActiveParticles+3] = CurrentParticle.Color.Alpha;

            ++ActiveParticles;
        }
        else{
            AvailablePositions.push(i);
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBO_POS_SIZE);
    glBufferData(GL_ARRAY_BUFFER, Particles.size() * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
    glBufferSubData(GL_ARRAY_BUFFER, 0, ActiveParticles * sizeof(GLfloat) * 4, GL_Position_Size_Buffer.data());

    glBindBuffer(GL_ARRAY_BUFFER, VBO_COLORS);
    glBufferData(GL_ARRAY_BUFFER, Particles.size() * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
    glBufferSubData(GL_ARRAY_BUFFER, 0, ActiveParticles * sizeof(GLubyte) * 4, GL_Color_Buffer.data());

}

void ParticleSystem::ParticleCreationHandler(){
    uint16_t FreePos;
    if(Timer.ElapsedTime().Seconds() > DELAY){
        Accumulator += Timer.ElapsedTime().Seconds();
        while(Accumulator > DELAY){
            Accumulator -= DELAY;

            FreePos = getFreePosition();

            #define SPEED 5

            Particles[FreePos].Position = glm::vec3(125, 10, -50);
            Particles[FreePos].Velocity = glm::vec3(
                gg::genFloatRandom(0, 1) * SPEED,
                gg::genFloatRandom(0, 1) * SPEED,
                gg::genFloatRandom(0, 1) * SPEED
            );

            Particles[FreePos].Color = gg::Color(
                gg::genIntRandom(0, 255),
                gg::genIntRandom(0, 255),
                gg::genIntRandom(0, 255)
            );

            Particles[FreePos].Life = 3.f;
            Particles[FreePos].Size = gg::genFloatRandom(1, 4);
        }
    }
}

uint16_t ParticleSystem::getFreePosition(){
    uint16_t FREE_POS = AvailablePositions.top();
    AvailablePositions.pop();

    uint16_t Next = FREE_POS;
    if(AvailablePositions.empty()){
        ++Next;
        if(Next >= Particles.size()){
            Next = 0;
        }
        AvailablePositions.push(Next);
    }
    return FREE_POS;
}

void ParticleSystem::Draw(){
    Particles_Shader->Bind();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    std::cout << "ActiveParticles " << ActiveParticles << '\n';
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Texture);
    glUniform1i(_U_DIFFUSE_MAP, 0);

    // glUniformMatrix4fv(_U_VP, 1, GL_FALSE, &ViewProjectionMatrix[0][0]);
    // glUniform3f(_U_CAM_UP   , ViewMatrix[0][1], ViewMatrix[1][1], ViewMatrix[2][1]);
    // glUniform3f(_U_CAM_RIGHT, ViewMatrix[0][0], ViewMatrix[1][0], ViewMatrix[2][0]);


    glBindVertexArray(PARTICLE_SYSTEM);
    glVertexAttribDivisor(0, 0);
    glVertexAttribDivisor(1, 1);
    glVertexAttribDivisor(2, 1);
    glBindVertexBuffer(0, VBO_SHAPE, 0, 12);
    glBindVertexBuffer(1, VBO_POS_SIZE, 0, 16);
    glBindVertexBuffer(2, VBO_COLORS, 0, 16);
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, ActiveParticles);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}
