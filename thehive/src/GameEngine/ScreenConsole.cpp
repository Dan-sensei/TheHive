#include "ScreenConsole.hpp"
#include <iostream>

irr::IrrlichtDevice* ScreenConsole::IrrlichtDevice = nullptr;

ScreenConsole::ScreenConsole(){

}

void ScreenConsole::AddTextToBuffer(const std::string &Text, const gg::Color &color){
    //irr::gui::IGUIFont* font = IrrlichtDevice->getGUIEnvironment()->getBuiltInFont();
    if(BUFFER.size()>41)
        BUFFER.pop_front();

    BUFFER.emplace_back(Text, color);

}

ScreenConsole::BufferText::BufferText(const std::string &_Text, const gg::Color &_Color)
:Text(_Text), Color(_Color)
{}

void ScreenConsole::DisplayDebug(){
    irr::gui::IGUIFont* font = IrrlichtDevice->getGUIEnvironment()->getFont("assets/Fonts/Debug.png");
    auto it = BUFFER.begin();
    uint16_t DiplayY = 10;
    while (it!=BUFFER.end()){
        irr::core::stringw WS((*it).Text.c_str());
        font->draw(WS, irr::core::rect<irr::s32>(20,DiplayY,700,50), irr::video::SColor((*it).Color.Alpha*255,(*it).Color.R,(*it).Color.G,(*it).Color.B));
        DiplayY += 17;
        ++it;
    }
}

void gg::cout (const std::string &Text, const gg::Color &color){
    Singleton<ScreenConsole>::Instance()->AddTextToBuffer(Text, color);
}

void gg::cout (const gg::Vector3f &Vector, const gg::Color &color){
    std::string VectorString = "(" + std::to_string(Vector.X) + "," + std::to_string(Vector.Y) + "," + std::to_string(Vector.Z) + ")";
    Singleton<ScreenConsole>::Instance()->AddTextToBuffer(VectorString, color);
}
