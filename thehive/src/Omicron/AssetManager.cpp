#include "AssetManager.hpp"
#include <iostream>
#include <SOIL2/SOIL2.h>

AssetManager::AssetManager(){
    ShaderMap["Nature"].loadFiles("assets/Shaders/VertexShader.glsl", nullptr, "assets/Shaders/FragmentShader.glsl");
    ShaderMap["Default"].loadFiles("assets/Shaders/VertexShader.glsl", nullptr, "assets/Shaders/FragmentShader.glsl");
    ShaderMap["Lines"].loadFiles("assets/Shaders/Line_VS.glsl", nullptr, "assets/Shaders/Line_FS.glsl");
    ShaderMap["2D"].loadFiles("assets/Shaders/VertexShader2D.glsl", nullptr, "assets/Shaders/FragmentShader2D.glsl");
    ShaderMap["Bill"].loadFiles("assets/Shaders/VertexShaderBillboard.glsl", nullptr, "assets/Shaders/FragmentShader2D.glsl");
    ShaderMap["Blend"].loadFiles("assets/Shaders/VertexShaderblend.glsl", nullptr, "assets/Shaders/FragmentShaderblend.glsl");
    ShaderMap["Plano"].loadFiles("assets/Shaders/VertexShader2DPlano.glsl", nullptr, "assets/Shaders/FragmentShader2DPlano.glsl");
    ShaderMap["skyboxShader"].loadFiles("assets/Shaders/SkyBox.vs", nullptr, "assets/Shaders/SkyBox.frag");
    ShaderMap["AnimationShader"].loadFiles("assets/Shaders/Animation.vs", nullptr, "assets/Shaders/FragmentShader.glsl");
    ShaderMap["Particles"].loadFiles("assets/Shaders/Particles_VS.glsl", nullptr, "assets/Shaders/Particles_FS.glsl");
    ShaderMap["DEFERRED"].loadFiles("assets/Shaders/Deferred_VS.glsl", nullptr, "assets/Shaders/Deferred_FS.glsl");
}

void AssetManager::loadInit(){
    Shader* shader = getShader("Default");
    ZMaterial* 		MAT = getMaterial("Default");
    MAT->attachShader(shader);
    MAT->addTexture(GN::DIFFUSE_MAP, "assets/Textures/DefaultDiffuse.jpg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    MAT->addTexture(GN::NORMAL_MAP, "assets/Textures/DefaultNormal.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    MAT->addTexture(GN::SPECULAR_MAP, "assets/Textures/DefaultSpecular.jpeg",   GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    MAT = getMaterial("Morado");
    MAT->attachShader(shader);
    MAT->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/prueba1.png",       		GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    MAT->addTexture(GN::NORMAL_MAP,       "assets/Textures/COMOUNPUTOPRO3.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    MAT->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Blue = getMaterial("Blue");
    Blue->attachShader(shader);
    Blue->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/Blue.png",       		     GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Blue->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Blue->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Nav = getMaterial("Nav");
    Nav->attachShader(shader);
    Nav->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/TEST.png",       		     GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Nav->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Nav->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);



    ZMaterial* 		Metal = getMaterial("Metal");
    Metal->attachShader(shader);
    Metal->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/metal.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Metal->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.png",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Metal->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Tree = getMaterial("Tree");
    Tree->attachShader(shader);
    Tree->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/Tree.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Tree->addTexture(GN::NORMAL_MAP,       "assets/Textures/Tree_Normals.png",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Tree->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Grey = getMaterial("Grey");
    Grey->attachShader(shader);
    Grey->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/grey.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Grey->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Grey->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Red = getMaterial("Red");
    Red->attachShader(shader);
    Red->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/red.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Red->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Red->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		White = getMaterial("White");
    White->attachShader(shader);
    White->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/white.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    White->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    White->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Ground = getMaterial("Ground");
    Ground->attachShader(shader);
    Ground->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/Asfalto_Diffuse.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Ground->addTexture(GN::NORMAL_MAP,       "assets/Textures/Asfalto_Normal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Ground->addTexture(GN::SPECULAR_MAP,     "assets/Textures/Asfalto_Gloss.jpg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Farola = getMaterial("Farola");
    Farola->attachShader(shader);
    Farola->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/farola1.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Farola->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Farola->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Car1 = getMaterial("Car1");
    Car1->attachShader(shader);
    Car1->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/car1.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Car1->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Car1->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Car2 = getMaterial("Car2");
    Car2->attachShader(shader);
    Car2->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/car2.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Car2->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Car2->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Car3 = getMaterial("Car3");
    Car3->attachShader(shader);
    Car3->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/car3.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Car3->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Car3->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Container = getMaterial("Container");
    Container->attachShader(shader);
    Container->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/Container.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Container->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Container->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Separador = getMaterial("Separador");
    Separador->attachShader(shader);
    Separador->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/Separador.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Separador->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Separador->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Trash = getMaterial("Trash");
    Trash->attachShader(shader);
    Trash->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/Trash.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Trash->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Trash->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		House = getMaterial("House");
    House->attachShader(shader);
    House->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/house.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    House->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    House->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		House2 = getMaterial("House2");
    House2->attachShader(shader);
    House2->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/brown.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    House2->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    House2->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Door = getMaterial("Door");
    Door->attachShader(shader);
    Door->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/door.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Door->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Door->addTexture(GN::SPECULAR_MAP,     "assets/Textures/Asfalto_Gloss.jpg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);




    shader = getShader("Blend");

    ZMaterial* 		Build = getMaterial("building");
    Build->attachShader(shader);
    Build->addTexture(GN::BLEND1,      "assets/Textures/edif.png",       		     GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Build->addTexture(GN::BLEND2,      "assets/Textures/edifluz.png",       		     GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    shader = getShader("AnimationShader");
    ZMaterial* Sold = getMaterial("Soldier");
    Sold->attachShader(shader);
    Sold->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/DefaultDiffuse.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Sold->addTexture(GN::NORMAL_MAP,       "assets/Textures/ALIEN.png",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Sold->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Hero = getMaterial("Hero");
    Hero->attachShader(shader);
    Hero->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/DefaultDiffuse.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Hero->addTexture(GN::NORMAL_MAP,       "assets/Textures/HERO_NORMALS3.png",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Hero->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);


    ZAnimationData* AnimationData = getAnimation("Soldier_Running");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/SoldierMov5.modelgg");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/SoldierMov4.modelgg");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/SoldierMov3.modelgg");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/SoldierMov2.modelgg");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/SoldierMov1.modelgg");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/SoldierMov0.modelgg");

    AnimationData = getAnimation("Hero_Standing");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/Standing3.modelgg");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/Standing2.modelgg");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/Standing1.modelgg");

    AnimationData = getAnimation("Hero_Walking");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/Walking4.modelgg");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/Walking3.modelgg");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/Walking2.modelgg");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/Walking1.modelgg");
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
