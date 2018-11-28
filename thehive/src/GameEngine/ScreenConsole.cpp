#include "ScreenConsole.hpp"
#include <iostream>
//#include <SMaterial>

irr::IrrlichtDevice* ScreenConsole::IrrlichtDevice = nullptr;
void ScreenConsole::setprogress(float prog){
    //std::cout << "entra en :" <<prog<< '\n';
    perc=1-prog;
}
ScreenConsole::ScreenConsole(){
    font = IrrlichtDevice->getGUIEnvironment()->getFont("assets/Fonts/Debug.png");


    AddImage("ojete","assets/HUD/ojetecalor.jpg",50,50);
    AddImage("mongol","assets/HUD/mongol.jpg",300,300);
    irr::video::IVideoDriver* driver = IrrlichtDevice->getVideoDriver();
    ancho=(driver->getScreenSize().Width/2);
    alto=(driver->getScreenSize().Height/2);
    //node->setMaterialTexture(0, driver->getTexture("bg.jpg"));
//redimensionar¿?
    //std::map <std::string,ImageHUD>::iterator it;
    //it=IMAGE_BUFFER.begin();
    //irr::video::SMaterial m;// = it->second.texture;
    //m.setTexture(0,it->second.texture);
    //m.getTextureMatrix(0).setTextureScale(.5f, .5f);
    perc=0;

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
        //driver->draw2DRectangle(irr::video::SColor(150,255,200,100),
        //irr::core::rect<irr::s32>(50,50,259,194));
        //259,194
        //if(perc<1){
        //    perc+=0.005;
        //}

        while(it!=IMAGE_BUFFER.end()){
            driver->draw2DImage(it->second.texture, irr::core::position2d<irr::s32>(it->second.posx,it->second.posy));
            //std::cout << "nombre" <<it->first<< '\n';
            //std::cout << "posx" <<it->second.posx<< '\n';
            //std::cout << "posy" <<it->second.posy<< '\n';
            //std::cout << "tamano H" <<it->second.texture->getSize().Height<< '\n';
            //std::cout << "tamano W" <<it->second.texture->getSize().Width<< '\n';
            //driver->draw2DRectangle(irr::video::SColor(150,255,0,0),
            //irr::core::rect<irr::s32>(it->second.posx,it->second.posy,it->second.posx+it->second.texture->getSize().Width,it->second.posy+it->second.texture->getSize().Height*perc));
            //irr::core::rect<irr::s32>(it->second.posx,it->second.posy,it->second.posx+it->second.texture->getSize().Width,it->second.posy+it->second.texture->getSize().Height));
            it++;
        }
        if(IMAGE_BUFFER.find("ojete")!=IMAGE_BUFFER.end()){
            it=IMAGE_BUFFER.find("ojete");
            //->second
            driver->draw2DRectangle(irr::video::SColor(150,255,0,0),
            irr::core::rect<irr::s32>(it->second.posx,it->second.posy,it->second.posx+it->second.texture->getSize().Width,it->second.posy+it->second.texture->getSize().Height*perc));

        }
         driver->draw2DLine(irr::core::position2d<irr::s32>(ancho-20,alto),irr::core::position2d<irr::s32>(ancho+20,alto),irr::video::SColor(250,0,0,0));
         driver->draw2DLine(irr::core::position2d<irr::s32>(ancho,alto-20),irr::core::position2d<irr::s32>(ancho,alto+20),irr::video::SColor(250,0,0,0));
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
