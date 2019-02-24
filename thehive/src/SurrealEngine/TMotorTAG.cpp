#include "TMotorTAG.hpp"

TMotorTAG::TMotorTAG(){
    ESCENA = new TNodo();
    gestorRecursos = Singleton<AssetManager>::Instance();
}

TMotorTAG::~TMotorTAG(){
    std::cout << "DeleTAG..." << '\n';
    delete ESCENA;

    // auto it = shaderMap.begin();
    // while(it != shaderMap.end()){
    //     delete it->second;
    // }
}

TNodo* TMotorTAG::crearCamara(const float& _fov, const float& _near, const float& _far, const gg::Vector3f& pos, const gg::Vector3f& rot, const float& _ppv){
    TCamara* C = new TCamara(_fov,_near,_far);
    C->setPerspectiva(_ppv);

    TNodo* Cam = new TNodo(bindTransform(pos,rot),C);

    return Cam;
}

TNodo* TMotorTAG::crearLuz(gg::Color &_color, const gg::Vector3f& pos, const gg::Vector3f& rot, const uint8_t& _sh){
    TLuz* L = new TLuz(_color,shaderMap.find(_sh)->second);
    TNodo* Luz = new TNodo(bindTransform(pos,rot),L);

    return Luz;
}

TNodo* TMotorTAG::crearMalla(const char* _path, const gg::Vector3f& pos, const gg::Vector3f& rot){
    ZStaticMesh* M = new ZStaticMesh();
    M->load(_path);

    TNodo* Malla = new TNodo(bindTransform(pos,rot),M);

    return Malla;
}

TNodo* TMotorTAG::bindTransform(const gg::Vector3f& pos, const gg::Vector3f& rot){
    TTransform* Rotate = new TTransform();
    TTransform* Translate = new TTransform();

    Rotate->rotate(rot.X, gg::Vector3f(1,0,0));
    Rotate->rotate(rot.Y, gg::Vector3f(0,1,0));
    Rotate->rotate(rot.Z, gg::Vector3f(0,0,1));
    Translate->translate(pos);

    TNodo* NodoRot = new TNodo(ESCENA,Rotate);
    TNodo* NodoTrans = new TNodo(NodoRot,Translate);

    return NodoTrans;
}

int8_t TMotorTAG::addShaderToMap(const char* _path,bool hasToBeBinded){
    Shader* _sh = AssetManager::getShader(_path);

    auto it = shaderMap.begin();
    uint8_t id = 0;

    if(hasToBeBinded){
        _sh->Bind();
    }

    while(it != shaderMap.end()){
        if(it->second == _sh){
            return it->first;
        }

        ++id;
        ++it;
    }

    shaderMap.insert(std::pair<uint8_t,Shader*>(id,_sh));
    return id;
}

bool TMotorTAG::bindMaterialToMesh(TNodo *_mesh,const char* _mat, const char* _diffuse, const char* _normal, const char* _specular, const uint8_t& _sh){
    ZStaticMesh*    O   = static_cast<ZStaticMesh*>(_mesh->getEntidad());
    ZMaterial* 		MAT = AssetManager::getMaterial("Morado");
	MAT->attachShader(shaderMap.find(_sh)->second);

	MAT->addTexture("DiffuseMap",      _diffuse,       GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
	MAT->addTexture("NormalMap",       _normal,        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
	MAT->addTexture("SpecularMap",     _specular,      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
	O->assignMaterial(MAT);

    return true;
}

void TMotorTAG::draw(){
    ESCENA->drawRoot();
}

void TMotorTAG::move(TNodo *_node, const gg::Vector3f& _offpos){
    static_cast<TTransform*>(_node->getPadre()->getEntidad())->translate(_offpos);
}

void TMotorTAG::rotate(TNodo *_node,const float& _angle,const gg::Vector3f& _offrot){
    static_cast<TTransform*>(_node->getPadre()->getPadre()->getEntidad())->rotate(_angle,_offrot);
}
