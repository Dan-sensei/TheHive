#include "TNodo.hpp"
#include <cstdint>
#include <iostream>

//Constructor para el nodo raiz
TNodo::TNodo()
:Visibility(true), entidad(nullptr), padre(nullptr)
{}

//Constructor para el resto de nodos
TNodo::TNodo(TNodo *P, TEntidad *_ent)
:Visibility(true), padre(P), entidad(_ent)
{
    P->addHijo(this);
}

TNodo::~TNodo(){
    for(uint16_t i = 0; i < hijos.size(); ++i)
        delete hijos[i];

    hijos.clear();

    delete entidad;
}

void TNodo::addHijo(TNodo* nodo){
    hijos.push_back(nodo);
}

void TNodo::remHijo(TNodo* nodo){
    for(uint16_t i = 0; i < hijos.size(); ++i){
        if(hijos[i] == nodo){
            hijos.erase(hijos.begin() + i);
            delete nodo;
            break;
        }
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

void TNodo::draw(){
    if(entidad){
        entidad->beginDraw();

        drawRoot();

        entidad->endDraw();
    }
    else{
        drawRoot();
    }
}

void TNodo::setVisibility(bool Flag){
    Visibility = Flag;
}


// Este para los demas
void TNodo::drawRoot(){
    if(!Visibility) return;
    auto it = hijos.begin();
    while(it != hijos.end()){
        (*it)->draw();
        ++it;
    }
}


void TNodo::ROOT_OkameraUpdate(){
    hijos[0]->draw();
}

void TNodo::ROOT_LightsUpdate(){
    hijos[1]->draw();
}

// Este es llamado desde el main (PURE ROOT)
void TNodo::drawRoot_M(){
    hijos[2]->draw();
}
