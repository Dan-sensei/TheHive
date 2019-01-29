#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <string>
#include <map>
#include "ZMeshData.hpp"
#include "ZMaterial.hpp"
#include "OpenGEnum.hpp"

class AssetManager {
    public:

        ~AssetManager();

        static ZMeshData* getMeshData(const std::string &Name);
        static ZMaterial* getMaterial(const std::string &Name);

    private:

        static std::map<std::string, ZMeshData> MeshDataMap;
        static std::map<std::string, ZMaterial> MaterialMap;

        AssetManager() = delete;
        AssetManager(const AssetManager &orig) = delete;
};

#endif