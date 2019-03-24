#ifndef NATURE_GENERATOR_HPP
#define NATURE_GENERATOR_HPP

#include <vector>
#include <array>
#include <GL/glew.h>
#include <cstdint>
#include <random>

// #include "Factory.hpp"
#include "Singleton.hpp"
#include "BinaryParser.hpp"
#include "AssetManager.hpp"
#include "Shader.hpp"
#include "ZMaterial.hpp"

#include "SurrealEngine/ZMeshData.hpp"
#include "SurrealEngine/ZStaticMesh.hpp"

class Factory;

class NatureGenerator {
    public:
        NatureGenerator();
        ~NatureGenerator();

        void init(const uint8_t &map_zone,glm::vec3 &Pos);
        void draw();
    private:
        AssetManager *Manager;
        Factory *fabrik;
        std::default_random_engine gen;
};

#endif
