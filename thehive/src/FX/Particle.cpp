#include "Particle.hpp"

Particle::Particle()
:Particle(glm::vec3(0,0,0), gg::Color(), 0, 1)
{}

Particle::Particle(const glm::vec3 &_Position, const gg::Color &_Color, float _Velocity, float _Life)
:Position(_Position), Color(_Color), Velocity(_Velocity), Life(_Life)
{}

Particle::Particle(const Particle &orig)
:Particle(orig.Position, orig.Color, orig.Velocity, orig.Life)
{}

Particle::~Particle(){}