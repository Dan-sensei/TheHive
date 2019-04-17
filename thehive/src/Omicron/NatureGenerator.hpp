#ifndef NATURE_GENERATOR_HPP
#define NATURE_GENERATOR_HPP

#include <vector>
#include <array>
#include <GL/glew.h>
#include <cstdint>
#include <random>

#include "Factory.hpp"
#include "Singleton.hpp"
#include "BinaryParser.hpp"
#include <Omicron/AssetManager.hpp>
#include "Shader.hpp"
#include <Omicron/ZMaterial.hpp>

class NatureGenerator {
    public:
        NatureGenerator();
        ~NatureGenerator();

        void init(const uint8_t &map_zone,const glm::vec3 &Pos);
        void update();
    private:
        AssetManager *Manager;
        Factory *fabrik;
        std::default_random_engine gen;
};

#endif
