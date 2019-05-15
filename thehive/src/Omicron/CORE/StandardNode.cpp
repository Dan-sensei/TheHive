#include "StandardNode.hpp"
#include <cstdint>
#include <iostream>

//Constructor para el nodo raiz
StandardNode::StandardNode()
:Visibility(true)
{}

//Constructor para el resto de nodos
StandardNode::StandardNode(ZNode *P, TEntidad *_ent)
:ZNode(P, _ent), Visibility(true)
{
    static_cast<StandardNode*>(P)->addHijo(this);
}

StandardNode::StandardNode(const StandardNode &orig)
:ZNode(orig.Padre, orig.Entidad)
{}

StandardNode::~StandardNode(){
    for(uint16_t i = 0; i < hijos.size(); ++i)
        delete hijos[i];

    hijos.clear();
}

void StandardNode::addHijo(ZNode* nodo){
    hijos.push_back(nodo);
}

void StandardNode::remHijo(ZNode* nodo){
    for(uint16_t i = 0; i < hijos.size(); ++i){
        if(hijos[i] == nodo){
            hijos.erase(hijos.begin() + i);
            delete nodo;
            break;
        }
    }
}

bool StandardNode::setPadre(ZNode *P){
    if(P){
        Padre = P;
        return true;
    }
    return false;
}

void StandardNode::draw(){
    if(Entidad){
        Entidad->beginDraw();

        drawRoot();

        Entidad->endDraw();
    }
    else{
        drawRoot();
    }
}

void StandardNode::setVisibility(bool Flag){
    Visibility = Flag;
}


// Este para los demas
void StandardNode::drawRoot(){
    if(!Visibility) return;
    auto it = hijos.begin();
    while(it != hijos.end()){
        (*it)->draw();
        ++it;
    }
}

bool StandardNode::isLeaf(){
    return false;
}

void StandardNode::ROOT_OkameraUpdate(){
    hijos[0]->draw();
}

void StandardNode::ROOT_LightsUpdate(){
    hijos[1]->draw();
}

// Este es llamado desde el main (PURE ROOT)
void StandardNode::ROOT_ObjectsUpdate(){
    hijos[2]->draw();
}

void StandardNode::ROOT_ForwardRendering(){
    hijos[3]->draw();
}
