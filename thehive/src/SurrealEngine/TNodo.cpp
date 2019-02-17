#include "TNodo.hpp"
#include <cstdint>



//Constructor para el nodo raiz
TNodo::TNodo(){
    padre = nullptr;
    entidad = nullptr;
    tipo_ent = 0;
}

//Constructor para el resto de nodos
TNodo::TNodo(TNodo *P,TEntidad *_ent){
    !P ? padre = nullptr : padre = P;
    !_ent?  entidad = nullptr : entidad = _ent;
    tipo_ent = 0;
}

TNodo::~TNodo(){
    auto it = hijos.begin();
    while(it!=hijos.end()){
        delete *it;
        ++it;
    }
    hijos.clear();

    delete entidad;
}

void TNodo::addHijo(TNodo* nodo){
    hijos.push_back(nodo);
}

void TNodo::remHijo(TNodo* nodo){

    auto it = hijos.begin();
    while(it != hijos.end()){
        if(*it == nodo){
            delete *it;
            hijos.erase(it);
            break;
        }
        ++it;
    }
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

bool TNodo::setPadre(TNodo *P){
    if(P){
        padre = P;
        return true;
    }
    return false;
}

TNodo* TNodo::getPadre(){
    return padre;
}

void TNodo::draw(uint8_t tipo_ent){

    entidad->beginDraw(tipo_ent);

    drawRoot();

    entidad->endDraw();
}

void TNodo::drawRoot(){
    auto it = hijos.begin();
    while(it != hijos.end()){
        (*it)->draw(tipo_ent);
        ++it;
    }

    tipo_ent++;
    if(tipo_ent == 3) tipo_ent = 0;

}
