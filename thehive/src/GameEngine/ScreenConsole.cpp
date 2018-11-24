#include "ScreenConsole.hpp"
#include <iostream>

irr::IrrlichtDevice* ScreenConsole::IrrlichtDevice = nullptr;

ScreenConsole::ScreenConsole(){
    font = IrrlichtDevice->getGUIEnvironment()->getFont("assets/Fonts/Debug.png");


    AddImage("ojete","assets/HUD/ojetecalor.jpg",50,50);
}
void ScreenConsole::AddImage(std::string palabra,std::string source,float _posx,float _posy){

irr::video::IVideoDriver* driver = IrrlichtDevice->getVideoDriver();
irr::video::ITexture* images = driver->getTexture(source.c_str());
IMAGE_BUFFER.insert(std::pair<std::string,ImageHUD>(palabra,ImageHUD(images,_posx,_posy)));


}
void ScreenConsole::AddTextToBuffer(const std::string &Text, const gg::Color &color){
    //irr::gui::IGUIFont* font = IrrlichtDevice->getGUIEnvironment()->getBuiltInFont();
    if(BUFFER.size()>35)
        BUFFER.pop_front();

    BUFFER.emplace_back(Text, color);

}

ScreenConsole::BufferText::BufferText(const std::string &_Text, const gg::Color &_Color)
:Text(_Text), Color(_Color)
{}
ScreenConsole::ImageHUD::ImageHUD(irr::video::ITexture* _texture,float _posx,float _posy)
:texture(_texture), posx(_posx),posy(_posy)
{}
void ScreenConsole::DisplayDebug(){
    if(true){
        irr::video::IVideoDriver* driver = IrrlichtDevice->getVideoDriver();
        //irr::video::ITexture* images = driver->getTexture("assets/HUD/ojetecalor.jpg");
        //driver->draw2DImage(images, irr::core::position2d<irr::s32>(50,50),
        //irr::core::rect<irr::s32>(0,0,342,224), 0,
        //irr::video::SColor(255,255,255,255), true);
        //driver->draw2DImage(images, irr::core::position2d<irr::s32>(50,50));

        std::map <std::string,ImageHUD>::iterator it;
        it=IMAGE_BUFFER.begin();
        while(it!=IMAGE_BUFFER.end()){
            driver->draw2DImage(it->second.texture, irr::core::position2d<irr::s32>(it->second.posx,it->second.posy));
            it++;
        }

    }
    if(true){
        auto it = BUFFER.begin();
        uint16_t DiplayY = 10;
        while (it!=BUFFER.end()){
            irr::core::stringw WS((*it).Text.c_str());
            font->draw(WS, irr::core::rect<irr::s32>(20,DiplayY,700,50), irr::video::SColor((*it).Color.Alpha*255,(*it).Color.R,(*it).Color.G,(*it).Color.B));
            DiplayY += 17;
            ++it;
        }
    }
}

void gg::cout (const std::string &Text, const gg::Color &color){
    Singleton<ScreenConsole>::Instance()->AddTextToBuffer(Text, color);
}

void gg::cout (const gg::Vector3f &Vector, const gg::Color &color){
    std::string VectorString = "(" + std::to_string(Vector.X) + "," + std::to_string(Vector.Y) + "," + std::to_string(Vector.Z) + ")";
    Singleton<ScreenConsole>::Instance()->AddTextToBuffer(VectorString, color);
}
