#include "Particle.hpp"

Particle::Particle()
:Particle(glm::vec3(0,0,0), glm::vec3(0,0,0), gg::Color(), 1, 1)
{}

Particle::Particle(const glm::vec3 &_Position, glm::vec3 _Velocity, const gg::Color &_Color, float _Life, float _Size)
:Position(_Position), Velocity(_Velocity), Color(_Color), Life(_Life)
{}

Particle::Particle(const Particle &orig)
:Particle(orig.Position, orig.Velocity, orig.Color, orig.Life, orig.Size)
{}

Particle::~Particle(){}
