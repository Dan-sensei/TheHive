#include "AssetManager.hpp"
#include <iostream>
#include <SOIL2/SOIL2.h>

AssetManager::AssetManager(){
    ShaderMap["Default"].loadFiles("assets/Shaders/VertexShader.glsl", nullptr, "assets/Shaders/FragmentShader.glsl");
    ShaderMap["Lines"].loadFiles("assets/Shaders/Line_VS.glsl", nullptr, "assets/Shaders/Line_FS.glsl");
    ShaderMap["2D"].loadFiles("assets/Shaders/VertexShader2D.glsl", nullptr, "assets/Shaders/FragmentShader2D.glsl");
    ShaderMap["Bill"].loadFiles("assets/Shaders/VertexShaderBillboard.glsl", nullptr, "assets/Shaders/FragmentShader2D.glsl");
    ShaderMap["Blend2D"].loadFiles("assets/Shaders/VertexShader2D.glsl", nullptr, "assets/Shaders/FragmentShader2DBlend.glsl");
    ShaderMap["Plano"].loadFiles("assets/Shaders/VertexShader2DPlano.glsl", nullptr, "assets/Shaders/FragmentShader2DPlano.glsl");
    ShaderMap["skyboxShader"].loadFiles("assets/Shaders/SkyBox.vs", nullptr, "assets/Shaders/SkyBox.frag");
    ShaderMap["AnimationShader"].loadFiles("assets/Shaders/Animation.vs", nullptr, "assets/Shaders/FragmentShader.glsl");
}

void AssetManager::loadInit(){
        Shader* Def = getShader("Default");

        ZMaterial*  Default = getMaterial("Default");
        Default->attachShader(Def);
        Default->addTexture("DiffuseMap", "assets/Textures/DefaultDiffuse.jpg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
        Default->addTexture("NormalMap", "assets/Textures/DefaultNormal.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
        Default->addTexture("SpecularMap", "assets/Textures/DefaultSpecular.jpeg",   GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

        ZMaterial* 		MAT = getMaterial("Morado");
        MAT->attachShader(Def);
        MAT->addTexture("DiffuseMap",      "assets/Textures/prueba1.png",       		GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
        MAT->addTexture("NormalMap",       "assets/Textures/COMOUNPUTOPRO3.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
        MAT->addTexture("SpecularMap",     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

        ZMaterial* 		Blue = getMaterial("Blue");
        Blue->attachShader(Def);
        Blue->addTexture("DiffuseMap",      "assets/Textures/Blue.png",       		    GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
        Blue->addTexture("NormalMap",       "assets/Textures/DefaultNormal.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
        Blue->addTexture("SpecularMap",     "assets/Textures/DefaultSpecular.jpeg",     GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

        ZMaterial* 		Nav = getMaterial("Nav");
        Nav->attachShader(Def);
        Nav->addTexture("DiffuseMap",      "assets/Textures/TEST.png",                  GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
        Nav->addTexture("NormalMap",       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
        Nav->addTexture("SpecularMap",     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

        ZMaterial* 		Hero = getMaterial("Hero");
        Hero->attachShader(Def);
        Hero->addTexture("DiffuseMap",      "assets/Textures/DefaultDiffuse.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
        Hero->addTexture("NormalMap",       "assets/Textures/HERO_NORMALS2.png",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
        Hero->addTexture("SpecularMap",     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

        ZMaterial* 		Sold = getMaterial("Soldier");
        Shader* anim = getShader("AnimationShader");
        std::cout << "ANIME SHADER " << anim << '\n';
        Sold->attachShader(anim);
        Sold->addTexture("DiffuseMap",      "assets/Textures/DefaultDiffuse.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
        Sold->addTexture("NormalMap",       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
        Sold->addTexture("SpecularMap",     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);


        ZAnimationData* Soldier = getAnimation("Soldier_Running");
        Soldier->addKeyframe("assets/BinaryFiles/BinaryModels/SoldierMov0.modelgg");
        Soldier->addKeyframe("assets/BinaryFiles/BinaryModels/SoldierMov1.modelgg");
        Soldier->addKeyframe("assets/BinaryFiles/BinaryModels/SoldierMov2.modelgg");
        Soldier->addKeyframe("assets/BinaryFiles/BinaryModels/SoldierMov3.modelgg");
        Soldier->addKeyframe("assets/BinaryFiles/BinaryModels/SoldierMov4.modelgg");
        Soldier->addKeyframe("assets/BinaryFiles/BinaryModels/SoldierMov5.modelgg");
}

ZMaterial* AssetManager::getMaterial(const std::string &Name) {

    auto it = MaterialMap.find(Name);
    if(it != MaterialMap.end()){
        return &it->second;
    }
    else {
        return &MaterialMap[Name];
    }
}

ZMeshData* AssetManager::getMeshData(const std::string &Name){

    auto it = MeshDataMap.find(Name);
    if(it != MeshDataMap.end())
        return &it->second;
    else{
        MeshDataMap[Name].load(Name);
        return &MeshDataMap[Name];
    }

}

Shader* AssetManager::getShader(const std::string &Name) {

    auto it = ShaderMap.find(Name);
    if(it != ShaderMap.end())
        return &it->second;
    else{
        std::cout << "  --No existe ningún Shader llamado '" << Name <<"', devolviendo 'Default'..." << '\n';
        return &ShaderMap["Default"];
    }
}

ZAnimationData* AssetManager::getAnimation(const std::string &Name){

    auto it = AnimationMap.find(Name);
    if(it != AnimationMap.end()){
        return &it->second;
    }
    else {
        return &AnimationMap[Name];
    }
}

Shader* AssetManager::createShader(std::string Name) {
    if(ShaderMap.find(Name) == ShaderMap.end())
        ShaderMap[Name];
    else
        std::cout << "  --Ya hay un shader con ese nombre" << '\n';

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
    std::cout << "Deleting textures..." << '\n';
    auto iterator = TextureMap.begin();
    while(iterator != TextureMap.end()){
        glDeleteTextures(1, &iterator->second);
        ++iterator;
    }
}
