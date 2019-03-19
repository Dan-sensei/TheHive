#include "TNodo.hpp"
#include <cstdint>

//Constructor para el nodo raiz
TNodo::TNodo()
:Visibility(true)
{
    padre = nullptr;
    entidad = nullptr;
}

//Constructor para el resto de nodos
TNodo::TNodo(TNodo *P,TEntidad *_ent)
:Visibility(true)
{
    !P ? padre = nullptr : padre = P;
    !_ent?  entidad = nullptr : entidad = _ent;

    P->addHijo(this);

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

void TNodo::draw(const uint8_t &T_ID){
    if(entidad){
        entidad->beginDraw(T_ID);

        drawRoot(T_ID);

        entidad->endDraw(T_ID);
    }
    else{
        drawRoot(T_ID);
    }
}

void TNodo::setVisibility(bool Flag){
    Visibility = Flag;
}

// Este es llamado desde el main (PURE ROOT)
void TNodo::drawRoot(){
    for(uint8_t REC = 0 ; REC < 3 ; ++REC){
        auto it = hijos.begin();
        while(it != hijos.end()){
            (*it)->draw(REC);
            ++it;
        }
    }
}

// Este para los demas
void TNodo::drawRoot(const uint8_t &T_ID){
    if(!Visibility) return;
    auto it = hijos.begin();
    while(it != hijos.end()){
        (*it)->draw(T_ID);
        ++it;
    }
}
