#include "Billboard.hpp"
#include <iostream>

Billboard::Billboard()
:billboard(nullptr)
{
}
Billboard::Billboard(const Billboard &orig){
    billboard = orig.billboard;
}
Billboard::~Billboard(){
    billboard->remove();
}

void Billboard::setText(const std::string &Text){
    std::wstring WS;
    WS.assign(Text.begin(), Text.end());
    billboard->setText(WS.c_str());
}

void Billboard::setColor(const uint8_t Color[4]){
    billboard->setColor(irr::video::SColor(Color[0], Color[1], Color[2], Color[3]));
}