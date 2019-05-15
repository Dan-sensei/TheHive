#include "Particle.hpp"

Particle::Particle()
:Particle(glm::vec3(0,0,0), glm::vec3(0,0,0), 0,0,0,255, 0, 0)
{}

Particle::Particle(const glm::vec3 &_Position, glm::vec3 _Velocity, uint8_t _R, uint8_t _G, uint8_t _B, uint8_t _A, float _Life, float _Size)
:Position(_Position), Velocity(_Velocity), R(_R), G(_G), B(_B), A(_A), Life(_Life), Size(_Size)
{}

Particle::Particle(const Particle &orig)
:Particle(orig.Position, orig.Velocity, orig.R, orig.G, orig.B, orig.A, orig.Life, orig.Size)
{}

Particle::~Particle(){}
