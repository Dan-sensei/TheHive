#include "IComponent.hpp"
#include <iostream>

IComponent::IComponent()
:EntityID(0)
{

}

IComponent::~IComponent(){

}


EMessageStatus IComponent::processMessage(){
    return ST_IGNORED;
}

void IComponent::setEntityID(uint16_t _ID){
    EntityID = _ID;
}

uint16_t IComponent::getEntityID(){
    return EntityID;
}
