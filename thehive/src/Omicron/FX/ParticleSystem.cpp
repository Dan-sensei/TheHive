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
    CurrentUpdate = &ParticleSystem::ResetTimerAndToggleUpdate;
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
        glVertexAttribFormat(1, 4, GL_FLOAT, false, 0);
        glVertexAttribFormat(2, 4, GL_UNSIGNED_BYTE, true, 0);

        glVertexAttribBinding(0, 0);
        glVertexAttribBinding(1, 1);
        glVertexAttribBinding(2, 2);

        glBindVertexBuffer(0, VBO_SHAPE, 0, 12);
        glBindVertexBuffer(1, VBO_POS_SIZE, 0, 16);
        glBindVertexBuffer(2, VBO_COLORS, 0, 16);

        glVertexAttribDivisor(0, 0);
        glVertexAttribDivisor(1, 1);
        glVertexAttribDivisor(2, 1);
    glBindVertexArray(0);
}

void ParticleSystem::setGenerationTime(float TIME_SECONDS){
    DELAY = TIME_SECONDS;
}

void ParticleSystem::setTexture(const std::string &_Texture){
    Texture = Singleton<AssetManager>::Instance()->getTexture(_Texture);
}

void ParticleSystem::beginDraw(){
    (this->*CurrentUpdate)();
}
void ParticleSystem::endDraw(){}

void ParticleSystem::ResetTimerAndToggleUpdate(){
    Timer.Restart();
    CurrentUpdate = &ParticleSystem::UpdateAndDraw;
    UpdateAndDraw();
}

void ParticleSystem::UpdateAndDraw(){
    Update();
    Draw();
}

void ParticleSystem::Update(){

    float Elapsed = 0;
    ParticleCreationHandler();

    ActiveParticles = 0;

    //uint16_t i = Particles.size();
    float ElapsedTime = Timer.Restart().Seconds();
    for(uint16_t i = 0; i < Particles.size(); ++i){

        Particle &CurrentParticle = Particles[i];
        CurrentParticle.Life -= ElapsedTime;
        if(CurrentParticle.Life > 0) {
            CurrentParticle.Position += CurrentParticle.Velocity * ElapsedTime;
            GL_Position_Size_Buffer[4*ActiveParticles+0] = CurrentParticle.Position.x;
            GL_Position_Size_Buffer[4*ActiveParticles+1] = CurrentParticle.Position.y;
            GL_Position_Size_Buffer[4*ActiveParticles+2] = CurrentParticle.Position.z;

            GL_Position_Size_Buffer[4*ActiveParticles+3] = CurrentParticle.Size;

            GL_Color_Buffer[4*ActiveParticles+0] = (GLubyte)CurrentParticle.Color.R;
            GL_Color_Buffer[4*ActiveParticles+1] = (GLubyte)CurrentParticle.Color.G;
            GL_Color_Buffer[4*ActiveParticles+2] = (GLubyte)CurrentParticle.Color.B;
            GL_Color_Buffer[4*ActiveParticles+3] = (GLubyte)CurrentParticle.Color.Alpha;

            ++ActiveParticles;
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBO_POS_SIZE);
    glBufferData(GL_ARRAY_BUFFER, Particles.size() * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, ActiveParticles * sizeof(GLfloat) * 4, GL_Position_Size_Buffer.data());

    glBindBuffer(GL_ARRAY_BUFFER, VBO_COLORS);
    glBufferData(GL_ARRAY_BUFFER, Particles.size() * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, ActiveParticles * sizeof(GLubyte) * 4, GL_Color_Buffer.data());
}

void ParticleSystem::ParticleCreationHandler(){
    uint16_t FreePos;

    Accumulator += Timer.ElapsedTime().Seconds();
    while(Accumulator > DELAY){
        Accumulator -= DELAY;

        FreePos = getFreePosition();

        #define SPEED 0.5f

        Particles[FreePos].Position = glm::vec3(-2.723060, 1.565783, -9.310295);
        Particles[FreePos].Velocity = glm::vec3(
            gg::genFloatRandom(-1, 1) * SPEED,
            gg::genFloatRandom(-1, 1) * SPEED,
            gg::genFloatRandom(-1, 1) * SPEED
        );

        Particles[FreePos].Color = gg::Color(
            gg::genIntRandom(0, 255),
            gg::genIntRandom(0, 255),
            gg::genIntRandom(0, 255)
        );
        std::cout << "Color " << (uint16_t)Particles[FreePos].Color.R << ", " << (uint16_t)Particles[FreePos].Color.G << ", " << (uint16_t)Particles[FreePos].Color.B << ", " << (uint16_t)Particles[FreePos].Color.Alpha << '\n';

        Particles[FreePos].Life = 4.f;
        Particles[FreePos].Size = gg::genFloatRandom(0.2f, 1);
    }
}

uint16_t ParticleSystem::getFreePosition(){
    for(uint16_t i=LastAvailablePosition; i < Particles.size(); i++){
		if (Particles[i].Life <= 0){
			LastAvailablePosition = i;
			return i;
		}
	}

	for(uint16_t i=0; i<LastAvailablePosition; i++){
		if (Particles[i].Life <= 0){
			LastAvailablePosition = i;
			return i;
		}
	}

	return 0;
}

void ParticleSystem::Draw(){
    Particles_Shader->Bind();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Texture);

    glm::mat4 VP = projMatrix*viewMatrix;
    glm::mat4 MV = viewMatrix*modelMatrix;

    glUniformMatrix4fv(_U_VP, 1, GL_FALSE, &VP[0][0]);
    glUniformMatrix4fv(9, 1, GL_FALSE, &MV[0][0]);
    glUniform3f(_U_CAM_UP   , viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1]);
    glUniform3f(_U_CAM_RIGHT, viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]);

    glBindVertexArray(PARTICLE_SYSTEM);
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, ActiveParticles);
}
