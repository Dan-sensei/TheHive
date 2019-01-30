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

        static ZMeshData*   getMeshData(const std::string &Name);
        static ZMaterial*   getMaterial(const std::string &Name);
        static unsigned int getTexture(const std::string &Name, unsigned int mode = 0, unsigned int flags = 0);
        static Shader*      getShader(const std::string& Name);

        static Shader*     createShader(std::string Name);

    private:

        static std::unordered_map<std::string, ZMeshData>       MeshDataMap;
        static std::unordered_map<std::string, ZMaterial>       MaterialMap;
        static std::unordered_map<std::string, Shader>          Shaders;
        static std::unordered_map<std::string, unsigned int>    TextureMap;

        AssetManager() = delete;
        AssetManager(const AssetManager &orig) = delete;
};

#endif