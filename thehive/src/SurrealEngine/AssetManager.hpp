#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <string>
#include <map>
#include "ZMesh.hpp"
#include "OpenGEnum.hpp"

class AssetManager {
    public:

        ~AssetManager();

        static void getMesh(const std::string &Name);
        static void getMaterial(const std::string &Name);

    private:

        static std::map<std::string, ZMesh> MeshMap;
        //static std::map<std::string, ZMaterial> MaterialMap;

        AssetManager() = delete;
        AssetManager(const AssetManager &orig) = delete;
};

#endif