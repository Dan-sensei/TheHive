#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <string>
#include <map>
#include "ZMeshData.hpp"
#include "ZAnimationData.hpp"
#include "ZMaterial.hpp"
#include "OpenGEnum.hpp"
#include "Singleton.hpp"
#include "BoundingBox.hpp"

template <typename T>
class Singleton;

class AssetManager {
    friend class Singleton<AssetManager>;
    public:

        ~AssetManager();
        void loadInit();

        ZMeshData*      getMeshData(const std::string &Name);
        ZAnimationData* getAnimation(const std::string &Name);
        ZMaterial*      getMaterial(const std::string &Name);
        unsigned int    getTexture(const std::string &Name, unsigned int mode = 0, unsigned int flags = 0);
        Shader*         getShader(const std::string& Name);

        Shader*     createShader(std::string Name);

    private:

        std::unordered_map<std::string, ZAnimationData>  AnimationMap;
        std::unordered_map<std::string, ZMeshData>       MeshDataMap;
        std::unordered_map<std::string, ZMaterial>       MaterialMap;
        std::unordered_map<std::string, Shader>          ShaderMap;
        std::unordered_map<std::string, unsigned int>    TextureMap;

        AssetManager();
        AssetManager(const AssetManager &orig) = delete;
};

#endif
