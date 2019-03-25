#include "AssetManager.hpp"
//#include <iostream>
#include <SOIL2/SOIL2.h>


std::unordered_map<std::string, ZMeshData> AssetManager::MeshDataMap;
std::unordered_map<std::string, ZMaterial> AssetManager::MaterialMap;
std::unordered_map<std::string, Shader> AssetManager::ShaderMap;
std::unordered_map<std::string, unsigned int> AssetManager::TextureMap;

AssetManager::AssetManager(){
    ShaderMap["Nature"].loadFiles("assets/Shaders/VertexShader.glsl", nullptr, "assets/Shaders/FragmentShader_NATURE.glsl");
    ShaderMap["Default"].loadFiles("assets/Shaders/VertexShader.glsl", nullptr, "assets/Shaders/FragmentShader.glsl");
    ShaderMap["Lines"].loadFiles("assets/Shaders/Line_VS.glsl", nullptr, "assets/Shaders/Line_FS.glsl");
    ShaderMap["2D"].loadFiles("assets/Shaders/VertexShader2D.glsl", nullptr, "assets/Shaders/FragmentShader2D.glsl");
    ShaderMap["Bill"].loadFiles("assets/Shaders/VertexShaderBillboard.glsl", nullptr, "assets/Shaders/FragmentShader2D.glsl");
    ShaderMap["Blend2D"].loadFiles("assets/Shaders/VertexShader2D.glsl", nullptr, "assets/Shaders/FragmentShader2DBlend.glsl");
    ShaderMap["Plano"].loadFiles("assets/Shaders/VertexShader2DPlano.glsl", nullptr, "assets/Shaders/FragmentShader2DPlano.glsl");
    ShaderMap["skyboxShader"].loadFiles("assets/Shaders/SkyBox.vs", nullptr, "assets/Shaders/SkyBox.frag");

    Shader* Def = getShader("Default");
    ZMaterial* 		MAT = getMaterial("Morado");
    MAT->attachShader(Def);
    MAT->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/prueba1.png",       		GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    MAT->addTexture(GN::NORMAL_MAP,       "assets/Textures/COMOUNPUTOPRO3.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    MAT->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    MAT = getMaterial("Blue");
    MAT->attachShader(Def);
    MAT->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/Blue.png",       		     GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    MAT->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    MAT->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    MAT = getMaterial("Nav");
    MAT->attachShader(Def);
    MAT->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/TEST.png",       		     GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    MAT->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    MAT->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    MAT = getMaterial("Hero");
    MAT->attachShader(Def);
    MAT->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/DefaultDiffuse.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    MAT->addTexture(GN::NORMAL_MAP,       "assets/Textures/HERO_NORMALS2.png",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    MAT->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    MAT = getMaterial("Alpha_Orange");
    MAT->attachShader(Def);
    MAT->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/ALPHA_ORANGE.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    MAT->addTexture(GN::NORMAL_MAP,       "assets/Textures/DeffaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    MAT->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    MAT = getMaterial("Alpha_Blue");
    MAT->attachShader(Def);
    MAT->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/ALPHA_BLUE.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    MAT->addTexture(GN::NORMAL_MAP,       "assets/Textures/DeffaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    MAT->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

}

ZMaterial* AssetManager::getMaterial(const std::string &Name) {

    auto it = MaterialMap.find(Name);
    if(it != MaterialMap.end())
        return &it->second;
    else {
        ZMaterial* newMat = &MaterialMap[Name];
        newMat->attachShader(&ShaderMap["Default"]);
        newMat->addTexture(GN::DIFFUSE_MAP, "assets/Textures/DefaultDiffuse.jpg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
        newMat->addTexture(GN::NORMAL_MAP, "assets/Textures/DefaultNormal.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
        newMat->addTexture(GN::SPECULAR_MAP, "assets/Textures/DefaultSpecular.jpeg",   GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

        return newMat;
    }
}

ZMeshData* AssetManager::getMeshData(const std::string &Name){

    auto it = MeshDataMap.find(Name);
    if(it != MeshDataMap.end())
        return &it->second;
    else{
        ZMeshData* ret = &MeshDataMap[Name];
        ret->load(Name);
        return ret;
    }

}

Shader* AssetManager::getShader(const std::string &Name) {

    auto it = ShaderMap.find(Name);
    if(it != ShaderMap.end())
        return &it->second;
    else{
        //std::cout << "  --No existe ningún Shader llamado '" << Name <<"', devolviendo 'Default'..." << '\n';
        return &ShaderMap["Default"];
    }

}

Shader* AssetManager::createShader(std::string Name) {
    if(ShaderMap.find(Name) == ShaderMap.end())
        ShaderMap[Name];

    return &ShaderMap[Name];
}

unsigned int AssetManager::getTexture(const std::string &Name, unsigned int mode, unsigned int flags){
    if(TextureMap.find(Name) != TextureMap.end()){
        return TextureMap[Name];
    }
    else {
        unsigned int NewID = SOIL_load_OGL_texture(Name.c_str(), mode, SOIL_CREATE_NEW_ID, flags );
        TextureMap.insert(std::make_pair(Name, NewID));
        return NewID;
    }
}

AssetManager::~AssetManager(){
    //std::cout << "Deleting textures..." << '\n';
    auto iterator = TextureMap.begin();
    while(iterator != TextureMap.end()){
        glDeleteTextures(1, &iterator->second);
        ++iterator;
    }
}
