#include "TNodo.hpp"

//Constructor para el nodo raiz
TNodo::TNodo(){
    padre = nullptr;
    entidad = nullptr;
}

//Constructor para el resto de nodos
TNodo::TNodo(TNodo *_papa,TEntidad *_ent){
    !_papa? padre = nullptr : padre = _papa;
    !_ent?  entidad = nullptr : entidad = _ent;
}

TNodo::~TNodo(){
    auto it = hijos.begin();
    int i = 0;

    while(it!=hijos.end()){
        delete hijos[i];
        hijos.erase(it);
        ++it;
        ++i;
    }
    // Con erase se borran las posiciones
    // Con shrink_to_fit se borra la memoria que ocupaba
    hijos.shrink_to_fit();

    delete entidad;

    // El puntero del padre no se borra nunca
    // Ya que se va recorriendo el arbol de arriba abajo
    // Sino se va a la puta
}

void TNodo::addHijo(TNodo* nodo){
    hijos.push_back(nodo);
}

void TNodo::remHijo(TNodo* nodo){
    for(int i=0 ; i<hijos.size() ; i++){
        if(hijos[i]==nodo){
            hijos.erase(hijos.begin()+i);
            break;
        }
    }

    // Necesario para evitar que recorra posiciones vacias
    hijos.shrink_to_fit();
}

bool TNodo::setEntidad(TEntidad *_ent){
    if(_ent){
        entidad = _ent;
        return true;
    }
    return false;
}

TEntidad* TNodo::getEntidad(){
    return entidad;
}

bool TNodo::setPadre(TNodo *_paapa){
    if(_paapa){
        padre = _paapa;
        return true;
    }
    return false;
}

TNodo* TNodo::getPadre(){
    return padre;
}

void TNodo::draw(){
    entidad->beginDraw();

    for(int i=0 ; i<hijos.size() ; i++)
        hijos[i]->draw();

    entidad->endDraw();
}
