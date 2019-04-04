#include "NatureGenerator.hpp"
#include <Omicron/BoundingBox.hpp>
#include "OpenGEnum.hpp"

NatureGenerator::NatureGenerator(){
    fabrik = Singleton<Factory>::Instance();
    Manager = Singleton<AssetManager>::Instance();
}

NatureGenerator::~NatureGenerator(){}

void NatureGenerator::init(const uint8_t &map_zone, const glm::vec3 &Pos){
    std::vector< float > PositionsNormals;
    std::vector< float > UV_Coords;
    std::vector< float > TangentsBitangents;
    std::vector< unsigned short > Indexes;

    std::string Path = "assets/BinaryFiles/BinaryModels/nature_test1.modelgg";
    std::string Path2 = "assets/BinaryFiles/BinaryModels/nature1.modelgg";

    bool loaded = BinaryParser::ImportMesh(Path, PositionsNormals, UV_Coords, TangentsBitangents, Indexes);
    if(!loaded){
        std::cout << "No se ha podido cargar la malla de vegetacion - " << Path << '\n';
        return;
    }

    glm::vec3 tmp_pos, tmp_rot;
    std::uniform_int_distribution<int> dist1(0,360);
    std::uniform_int_distribution<int> dist2(0,10);

    // Shader* Shader = Manager->getShader("Nature");
    Shader* Shader = Manager->getShader("Default");
    ZMaterial* Material = Manager->getMaterial("Nature");
    Material->attachShader(Shader);
    Material->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/Nature/plant.png",       		GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Material->addTexture(GN::NORMAL_MAP,       "assets/Textures/COMOUNPUTOPRO3.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Material->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    // ZMaterial* Material = Manager->getMaterial("Blue");

    // fabrik->createNatureMesh(Path2,Pos,glm::vec3(),Material,map_zone);

    for (size_t i = 0; i < PositionsNormals.size(); i+=6) {
        if(dist2(gen)>8){
            tmp_pos = glm::vec3(
                Pos.x+PositionsNormals[i],
                Pos.y+PositionsNormals[i+1],
                Pos.z+PositionsNormals[i+2]
            );
            tmp_rot = glm::vec3(0,dist1(gen),0);

            fabrik->createNatureMesh(Path2,tmp_pos,tmp_rot,Material,map_zone+1);
        }
    }

}


void NatureGenerator::update(){
    // std::cout << "UPDATE NATURE" << '\n';
    // Shader *sh = Manager->getShader("Nature");
    // sh->Bind();
    // GLuint UL;

    // UL = sh->getUniformLocation("GS_POSITIONS");
    // if(UL == 0xFFFFFFFF) std::cout << "Cacho mierda, no ha cogido la ubicacion de GS_POSITIONS" << '\n';
    // glUniform1fv(UL,GS_SIZE,&tmp_positions[0]);

    // UL = sh->getUniformLocation("GS_SIZE");
    // if(UL == 0xFFFFFFFF) std::cout << "Cacho mierda, no ha cogido la ubicacion de GS_SIZE" << '\n';
    // glUniform1i(UL,GS_SIZE);
}
