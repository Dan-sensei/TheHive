#include "ScreenConsole.hpp"
#include <iostream>
//#include <SMaterial>
#include <GameEngine/EnumButtonType.hpp>

irr::IrrlichtDevice* ScreenConsole::IrrlichtDevice = nullptr;
void ScreenConsole::setprogress(int hab,float prog){
    //// std::cout << "entra en :" <<prog<< '\n';
    if(hab==0){
        perc=1-prog;

    }else if(hab==1){
        perc2=1-prog;

    }
    else{
        perc3=1-prog;

    }
}
void ScreenConsole::setvida(float _vida){
    // std::cout << "hacemos algo" << '\n';
vida=_vida;
}
void ScreenConsole::setbullet(int tipo,int balas){
    if(tipo==0){
        balaP=balas;

    }else {
        balaS=balas;
    }
}

float ScreenConsole::porc_alto(float x){
    return ((alto*2)/100.0)*x;
}
float ScreenConsole::porc_ancho(float x){
    return ((ancho*2)/100.0)*x;
}
ScreenConsole::ScreenConsole(){
    font = IrrlichtDevice->getGUIEnvironment()->getFont("assets/Fonts/Debug.png");
    //IrrlichtDevice->getGUIEnvironment()->a
    //IGUIEnvironment* env = device->getGUIEnvironment();
    irr::video::IVideoDriver* driver = IrrlichtDevice->getVideoDriver();

    ancho=(driver->getScreenSize().Width/2);
    alto=(driver->getScreenSize().Height/2);
}
//Menu principal
int ScreenConsole::InitPause(){
    CLIN();
    addButton(45,50,55,59,CONTINUE,"Continuar",true);
    addButton(45,60,55,69,DIFF2,"Ni puta idea");
    addButton(45,70,55,79,RETURNMENU,"Salir al menu");
    return 3;
}
int ScreenConsole::InitMenu(){
    CLIN();
    AddStaticTextToBuffer(porc_ancho(45),porc_alto(10),std::string("Menu principal"),gg::Color(0,0,0,1));
    //AddStaticTextToBuffer(porc_ancho(45),porc_alto(10),std::string("Menu principal"),gg::Color(1,255,255,255));

    //IrrlichtDevice->getGUIEnvironment()->addStaticText (L"Menu principal",irr::core::rect<irr::s32>(porc_ancho(45),porc_alto(10),porc_ancho(55),porc_alto(30)));

    //IrrlichtDevice->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(porc_ancho(38),porc_alto(50),porc_ancho(48),porc_alto(70)), 0, 0,
    //            L"J");
    addButton(38,50,48,70,GOPLAY,"J");
    addButton(38,75,48,95,GOCREDITS,"C");
    addButton(52,50,62,70,GOOPTIONS,"O");
    addButton(52,75,62,95,CLOSE,"S");
    return 4;
}
//Jugar
int ScreenConsole::InitMenu2(){
    CLIN();
    AddStaticTextToBuffer(porc_ancho(45),porc_alto(10),std::string("Play"),gg::Color(0,0,0,1));
    addButton(45,50,55,59,DIFF1,"Larva",true);
    addButton(45,60,55,69,DIFF2,"Alien");
    addButton(45,70,55,79,DIFF3,"The hive");
    addButton(40,80,60,89,START,"Play");

    addButton(65,80,70,89,GOMAIN,"Back");
return 5;
}
//Creditos
int ScreenConsole::InitMenu3(){
    CLIN();
    AddStaticTextToBuffer(porc_ancho(45),porc_alto(10),std::string("Credits"),gg::Color(0,0,0,1));

    addButton(65,80,70,89,GOMAIN,"Back");
    return 1;
}
//Opciones
int ScreenConsole::InitMenu4(){
    CLIN();
    AddStaticTextToBuffer(porc_ancho(45),porc_alto(10),std::string("Options"),gg::Color(0,0,0,1));

    addButton(45,50,55,59,GOVIDEO,"Video");
    addButton(45,60,55,69,GOMUSIC,"Music");
    addButton(45,70,55,79,GOCONTROLLS,"Controlls");

    addButton(65,80,70,89,GOMAIN,"Back");
    return 4;
}
//graficos
int ScreenConsole::InitMenu5(){
    CLIN();
    AddStaticTextToBuffer(porc_ancho(45),porc_alto(10),std::string("Video"),gg::Color(0,0,0,1));

    addButton(65,80,70,89,GOOPTIONS,"Back");
    return 1;
}
//sonido
int ScreenConsole::InitMenu6(){
    CLIN();
    AddStaticTextToBuffer(porc_ancho(45),porc_alto(10),std::string("Audio"),gg::Color(0,0,0,1));

    addButton(65,80,70,89,GOOPTIONS,"Back");
    return 1;
}
//controles
int ScreenConsole::InitMenu7(){
    CLIN();
    AddStaticTextToBuffer(porc_ancho(45),porc_alto(10),std::string("Controlls"),gg::Color(0,0,0,1));

    addButton(65,80,70,89,GOOPTIONS,"Back");
return 1;
    //IrrlichtDevice->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(porc_ancho(65),porc_alto(80),porc_ancho(70),porc_alto(89)), 0, 2);
    //AddStaticTextToBuffer(porc_ancho(65.5),porc_alto(83),std::string("Back"),gg::Color(0,0,0,1));
}
//Singleton<ScreenConsole>::Instance()->Pulsarboton(cursorpos);

int ScreenConsole::Pulsarboton(int but){
    return Botones.at(but)->getID();
}
void ScreenConsole::addButton(float x, float y, float w,float h,int id,std::string texto, bool focus){
    //irr::core::stringw WS(texto.c_str());
    std::wstring widestr = std::wstring(texto.begin(), texto.end());
    const wchar_t* szName = widestr.c_str();
    auto hola=font->getDimension (szName);

    float _x=porc_ancho(x);
    float _y=porc_alto(y);
    float _w=porc_ancho(w);
    float _h=porc_alto(h);
    auto gen=IrrlichtDevice->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(_x,_y,_w,_h), 0, id);
    Botones.push_back(gen);
    if(focus){
        IrrlichtDevice->getGUIEnvironment()->setFocus(gen);
    }

    float difx=(_w-_x-hola.Width)/2.0;
    float dify=(_h-_y-hola.Height)/2.0;
//x=10y=100/3
    AddStaticTextToBuffer(_x+difx,_y+dify,texto,gg::Color(0,0,0,1));


}
void ScreenConsole::InitHUD(){


    AddImage("hab1","assets/HUD/ojetecalor.jpg",porc_ancho(2),porc_alto(90),porc_alto(10),porc_alto(10));
    AddImage("hab2","assets/HUD/ojetecalor.jpg",porc_ancho(9),porc_alto(90),porc_alto(10),porc_alto(10));
    AddImage("hab3","assets/HUD/ojetecalor.jpg",porc_ancho(16),porc_alto(90),porc_alto(10),porc_alto(10));

    AddImage("1arma","assets/HUD/ojetecalor.jpg",porc_ancho(70),porc_alto(80),porc_ancho(20),porc_alto(15));//principal
    AddImage("0arma","assets/HUD/ojetecalor.jpg",porc_ancho(75),porc_alto(85),porc_ancho(20),porc_alto(15));

    AddImage("vida","assets/HUD/ojetecalor.jpg",porc_ancho(60),porc_alto(2),porc_ancho(30),porc_alto(3));

    AddImage("G1","assets/HUD/ojetecalor.jpg",porc_ancho(2),porc_alto(2),porc_alto(10),porc_alto(10));
    AddImage("G2","assets/HUD/ojetecalor.jpg",porc_ancho(13),porc_alto(2),porc_alto(10),porc_alto(10));
    AddImage("G3","assets/HUD/ojetecalor.jpg",porc_ancho(24),porc_alto(2),porc_alto(10),porc_alto(10));
    perc=0;
    perc2=0;
    perc3=0;
    balaP=0;
    balaS=0;
    vida=1;

}
void ScreenConsole::AddImage(std::string palabra,std::string source,float _posx,float _posy,float _width,float _height){

    irr::video::IVideoDriver* driver = IrrlichtDevice->getVideoDriver();
    irr::video::ITexture* images = driver->getTexture(source.c_str());
    IMAGE_BUFFER.insert(std::pair<std::string,ImageHUD>(palabra,ImageHUD(images,_posx,_posy,_width,_height)));

}
void ScreenConsole::AddTextToBuffer(const std::string &Text, const gg::Color &color){
    //irr::gui::IGUIFont* font = IrrlichtDevice->getGUIEnvironment()->getBuiltInFont();
    if(BUFFER.size()>35)
        BUFFER.pop_front();

    BUFFER.emplace_back(Text, color);

}
void ScreenConsole::AddStaticTextToBuffer(int x,int y, std::string Text,  gg::Color color){

    TEXT_BUFFER.emplace_back(x,y,Text, color);
}
ScreenConsole::BufferText::BufferText(const std::string &_Text, const gg::Color &_Color)
:Text(_Text), Color(_Color)
{}
ScreenConsole::StaticText::StaticText(float _x,float _y, std::string _Text,gg::Color _Color)
:Text(_Text),Color(_Color),posx(_x),posy(_y)
{}
ScreenConsole::ImageHUD::ImageHUD(irr::video::ITexture* _texture,float _posx,float _posy,float _width,float _height)
:texture(_texture), posx(_posx),posy(_posy),width(_width),height(_height)
{}
void ScreenConsole::CLIN(){
    BUFFER.clear();
    TEXT_BUFFER.clear();
    Botones.clear();
    IMAGE_BUFFER.clear();
    IrrlichtDevice->getGUIEnvironment()->clear();


}
void ScreenConsole::DisplayDebug(){
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
void ScreenConsole::DisplayMenu(){
    IrrlichtDevice->getGUIEnvironment()->drawAll();
    auto it = TEXT_BUFFER.begin();
    while (it!=TEXT_BUFFER.end()){
        irr::core::stringw WS((*it).Text.c_str());
        font->draw(WS, irr::core::rect<irr::s32>((*it).posx,(*it).posy,(*it).posx+100,(*it).posy+100),irr::video::SColor((*it).Color.Alpha*255,(*it).Color.R,(*it).Color.G,(*it).Color.B));
        //DiplayY += 17;
        //->draw(L"Menu principal", irr::core::rect<irr::s32>(porc_ancho(45),porc_alto(10),porc_ancho(55),porc_alto(30)), irr::video::SColor(255,155,155,155));
        ++it;
    }
    //IrrlichtDevice->getGUIEnvironment()->addStaticText (L"Menu principal",irr::core::rect<irr::s32>(porc_ancho(45),porc_alto(10),porc_ancho(55),porc_alto(30)));
    //font->draw(L"Menu principal", irr::core::rect<irr::s32>(porc_ancho(45),porc_alto(10),porc_ancho(55),porc_alto(30)), irr::video::SColor(255,155,155,155));


}
void ScreenConsole::DisplayHUD(){
    if(true){
        irr::video::IVideoDriver* driver = IrrlichtDevice->getVideoDriver();
        std::map <std::string,ImageHUD>::iterator it;
        it=IMAGE_BUFFER.begin();
        while(it!=IMAGE_BUFFER.end()){
            driver->draw2DImage(it->second.texture,
                irr::core::rect<irr::s32>(it->second.posx,it->second.posy,it->second.posx+it->second.width,it->second.posy+it->second.height),
                irr::core::rect<irr::s32>(0,0,it->second.texture->getSize().Width,it->second.texture->getSize().Height)
            );
            it++;
        }
        if(IMAGE_BUFFER.find("hab1")!=IMAGE_BUFFER.end()){
            it=IMAGE_BUFFER.find("hab1");
            driver->draw2DRectangle(irr::video::SColor(150,255,0,0),
            irr::core::rect<irr::s32>(it->second.posx,it->second.posy,it->second.posx+it->second.width,it->second.posy+it->second.height*perc));
        }
        if(IMAGE_BUFFER.find("hab2")!=IMAGE_BUFFER.end()){
            it=IMAGE_BUFFER.find("hab2");
            driver->draw2DRectangle(irr::video::SColor(150,255,0,0),
            irr::core::rect<irr::s32>(it->second.posx,it->second.posy,it->second.posx+it->second.width,it->second.posy+it->second.height*perc2));
        }
        if(IMAGE_BUFFER.find("hab3")!=IMAGE_BUFFER.end()){
            it=IMAGE_BUFFER.find("hab3");
            driver->draw2DRectangle(irr::video::SColor(150,255,0,0),
            irr::core::rect<irr::s32>(it->second.posx,it->second.posy,it->second.posx+it->second.width,it->second.posy+it->second.height*perc3));
        }
        if(IMAGE_BUFFER.find("vida")!=IMAGE_BUFFER.end()){
            it=IMAGE_BUFFER.find("vida");
            driver->draw2DRectangle(irr::video::SColor(150,0,255,0),
            irr::core::rect<irr::s32>(it->second.posx,it->second.posy,it->second.posx+it->second.width*vida,it->second.posy+it->second.height));
        }
        if(IMAGE_BUFFER.find("1arma")!=IMAGE_BUFFER.end()){
            it=IMAGE_BUFFER.find("1arma");
            std::string hola=std::to_string(balaP)+std::string("/100");
            font->draw(hola.c_str(), irr::core::rect<irr::s32>(it->second.posx+(it->second.width/100)*65,it->second.posy+(it->second.height/100)*70,700,50), irr::video::SColor(150,255,0,0));
        }
        if(IMAGE_BUFFER.find("0arma")!=IMAGE_BUFFER.end()){
            it=IMAGE_BUFFER.find("0arma");
            std::string hola=std::to_string(balaS)+std::string("/100");
            font->draw(hola.c_str(), irr::core::rect<irr::s32>(it->second.posx+(it->second.width/100)*65,it->second.posy+(it->second.height/100)*70,700,50), irr::video::SColor(150,255,0,0));
        }
        float ale=porc_alto(2);
        driver->draw2DLine(irr::core::position2d<irr::s32>(ancho-ale,alto),irr::core::position2d<irr::s32>(ancho+ale,alto),irr::video::SColor(250,0,0,0));
        driver->draw2DLine(irr::core::position2d<irr::s32>(ancho,alto-ale),irr::core::position2d<irr::s32>(ancho,alto+ale),irr::video::SColor(250,0,0,0));
    }
}
void gg::cout (const std::string &Text, const gg::Color &color){
    Singleton<ScreenConsole>::Instance()->AddTextToBuffer(Text, color);
}
void gg::cout (const gg::Vector3f &Vector, const gg::Color &color){
    std::string VectorString = "(" + std::to_string(Vector.X) + "," + std::to_string(Vector.Y) + "," + std::to_string(Vector.Z) + ")";
    Singleton<ScreenConsole>::Instance()->AddTextToBuffer(VectorString, color);
}
