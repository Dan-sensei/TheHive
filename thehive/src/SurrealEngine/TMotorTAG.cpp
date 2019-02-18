#include "TMotorTAG.hpp"


TMotorTAG::TMotorTAG(){

    escena = new TNodo();
    gestorRecursos = Singleton<AssetManager>::Instance();
}

TMotorTAG::~TMotorTAG(){}

TNodo* TMotorTAG::crearNodo(TNodo *padre, TEntidad *entidad){

    TNodo* N = new TNodo();
    if(padre!=nullptr && entidad!=nullptr){
        N->setPadre(padre);
        N->setEntidad(entidad);
    }

    return N;
}


TNodo* TMotorTAG::crearCamara(float _fov, float _near, float _far, gg::Vector3f pos, gg::Vector3f rot){

    TCamara* C = new TCamara(_fov,_near,_far);

    TNodo* Cam = new TNodo(Transform(pos,rot),C);

    return Cam;

}

TNodo* TMotorTAG::crearLuz(gg::Color &_color, gg::Vector3f pos, gg::Vector3f rot){

    TLuz* L = new TLuz(_color);

    TNodo* Luz = new TNodo(Transform(pos,rot),L);

    return Luz;

}

TNodo* TMotorTAG::crearMalla(const std::string& Name, gg::Vector3f pos, gg::Vector3f rot){

    ZStaticMesh* M = new ZStaticMesh();
    M->load(Name);

    TNodo* Malla = new TNodo(Transform(pos,rot),M);

    return Malla;

}

TNodo* TMotorTAG::Transform(gg::Vector3f pos, gg::Vector3f rot){

    TTransform* Translate = new TTransform();
    TTransform* Rotate = new TTransform();

    Rotate->rotate(rot.X, gg::Vector3f(1,0,0));
    Rotate->rotate(rot.Y, gg::Vector3f(0,1,0));
    Rotate->rotate(rot.Z, gg::Vector3f(0,0,1));
    Translate->translate(pos);

    TNodo* NodoRot = new TNodo(escena,Rotate);
    TNodo* NodoTrans = new TNodo(NodoRot,Translate);

    return NodoTrans;
}
