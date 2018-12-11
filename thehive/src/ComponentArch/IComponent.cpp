#include "IComponent.hpp"
#include <iostream>

IComponent::IComponent()
:EntityID(0)
{

}

IComponent::~IComponent(){

}


gg::EMessageStatus IComponent::processMessage(const Message &m){
    return gg::ST_IGNORED;
}

void IComponent::setEntityID(uint16_t _ID){
    EntityID = _ID;
}

uint16_t IComponent::getEntityID(){
    return EntityID;
}

void IComponent::Init(){}
void IComponent::Update(){}
void IComponent::FixedUpdate(){}
