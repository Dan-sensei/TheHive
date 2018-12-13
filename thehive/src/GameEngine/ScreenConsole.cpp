#include "ScreenConsole.hpp"
#include <iostream>
//#include <SMaterial>

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
    irr::video::IVideoDriver* driver = IrrlichtDevice->getVideoDriver();

    ancho=(driver->getScreenSize().Width/2);
    alto=(driver->getScreenSize().Height/2);

    AddImage("hab1","assets/HUD/ojetecalor.jpg",porc_ancho(2),porc_alto(90),porc_alto(10),porc_alto(10));
    AddImage("hab2","assets/HUD/ojetecalor.jpg",porc_ancho(9),porc_alto(90),porc_alto(10),porc_alto(10));
    AddImage("hab3","assets/HUD/ojetecalor.jpg",porc_ancho(16),porc_alto(90),porc_alto(10),porc_alto(10));

    AddImage("0arma","assets/HUD/ojetecalor.jpg",porc_ancho(75),porc_alto(85),porc_ancho(20),porc_alto(15));
    AddImage("1arma","assets/HUD/ojetecalor.jpg",porc_ancho(70),porc_alto(80),porc_ancho(20),porc_alto(15)); // Principal

    AddImage("vida","assets/HUD/ojetecalor.jpg",porc_ancho(60),porc_alto(2),porc_ancho(30),porc_alto(3));

    AddImage("G1","assets/HUD/ojetecalor.jpg",porc_ancho(2),porc_alto(2),porc_alto(10),porc_alto(10));
    AddImage("G2","assets/HUD/ojetecalor.jpg",porc_ancho(13),porc_alto(2),porc_alto(10),porc_alto(10));
    AddImage("G3","assets/HUD/ojetecalor.jpg",porc_ancho(24),porc_alto(2),porc_alto(10),porc_alto(10));

    // MAPA A FUNCIONES MOLON
    mapHudFunctions.insert(std::make_pair("hab1",&ScreenConsole::HUD_hability1));
    mapHudFunctions.insert(std::make_pair("hab2",&ScreenConsole::HUD_hability2));
    mapHudFunctions.insert(std::make_pair("hab3",&ScreenConsole::HUD_hability3));
    mapHudFunctions.insert(std::make_pair("vida",&ScreenConsole::HUD_vida));
    mapHudFunctions.insert(std::make_pair("0arma",&ScreenConsole::HUD_arma0));
    mapHudFunctions.insert(std::make_pair("1arma",&ScreenConsole::HUD_arma1));

    //AddImage("mongol","assets/HUD/mongol.jpg",300,300,30,30);
    //node->setMaterialTexture(0, driver->getTexture("bg.jpg"));
//redimensionar¿?
//    std::map <std::string,ImageHUD>::iterator it;
//    it=IMAGE_BUFFER.begin();
//    matrix4* tran = it->second.texture->getTextureMatrix();

    //ITexture* background = driver->getTexture("bg2.jpg");
       //matrix4* tran = background->getTextureMatrix();
       //tran->setScale(vector3df(0.5f,0.5f,0.5f));


//    irr::video::SMaterial m;// = it->second.texture;
//    m.setTexture(0,it->second.texture);
//    m.getTextureMatrix(0).setTextureScale(.3f, .5f);
    //irr::core::CMatrix4<float> k=m.getTextureMatrix(0);
    //// std::cout << k[66] << '\n';
//    // std::cout << k.getScale().X << '\n';
    //// std::cout << m.getTextureMatrix(0) << '\';
    //m.getTextureMatrix(0)[0][0][0][0];
    //CMatrix4<float> k=m.getTextureMatrix(0);
    perc    =   0;
    perc2   =   0;
    perc3   =   0;
    balaP   =   0;
    balaS   =   0;
    vida    =   1;

}

void ScreenConsole::AddImage(std::string palabra,std::string source,float _posx,float _posy,float _width,float _height){
    driver = IrrlichtDevice->getVideoDriver();
    irr::video::ITexture* images = driver->getTexture(source.c_str());
    // IMAGE_BUFFER.insert(std::pair<std::string,ImageHUD>(palabra,ImageHUD(images,_posx,_posy,_width,_height)));
    IMAGE_BUFFER.push_back(std::make_pair(palabra,ImageHUD(images,_posx,_posy,_width,_height)));
}

void ScreenConsole::AddTextToBuffer(const std::string &Text, const gg::Color &color){
    if(BUFFER.size()>35)
        BUFFER.pop_front();

    BUFFER.emplace_back(Text, color);
}

ScreenConsole::BufferText::BufferText(const std::string &_Text, const gg::Color &_Color)
:Text(_Text), Color(_Color)
{}

ScreenConsole::ImageHUD::ImageHUD(irr::video::ITexture* _texture,float _posx,float _posy,float _width,float _height)
:texture(_texture), posx(_posx),posy(_posy),width(_width),height(_height)
{}

void ScreenConsole::DisplayDebug(){
    if(true){
        //irr::video::ITexture* images = driver->getTexture("assets/HUD/ojetecalor.jpg");
        //driver->draw2DImage(images, irr::core::position2d<irr::s32>(50,50),
        //irr::core::rect<irr::s32>(0,0,342,224), 0,
        //irr::video::SColor(255,255,255,255), true);
        //driver->draw2DImage(images, irr::core::position2d<irr::s32>(50,50));

        std::vector<std::pair<std::string,ImageHUD>>::iterator it = IMAGE_BUFFER.begin();
        float X,Y,H,W,T_W,T_H;
        while(it!=IMAGE_BUFFER.end()){
            ImageHUD img    = it->second;
            X               = img.posx;
            Y               = img.posy;
            H               = img.height;
            W               = img.width;
            T_W             = img.texture->getSize().Width;
            T_H             = img.texture->getSize().Height;
            driver->draw2DImage(
                img.texture,
                irr::core::rect<irr::s32>(X,Y,X+W,Y+H),
                irr::core::rect<irr::s32>(0,0,T_W,T_H)
            );

            if(mapHudFunctions.find(it->first) != mapHudFunctions.end())
                (this->*mapHudFunctions[it->first])(it->second);

            it++;
        }

        //AddImage("G3","assets/HUD/ojetecalor.jpg",porc_ancho(24),porc_alto(2),porc_alto(10),porc_alto(10));
        float ale=porc_alto(2);
        driver->draw2DLine(irr::core::position2d<irr::s32>(ancho-ale,alto),irr::core::position2d<irr::s32>(ancho+ale,alto),irr::video::SColor(250,0,0,0));
        driver->draw2DLine(irr::core::position2d<irr::s32>(ancho,alto-ale),irr::core::position2d<irr::s32>(ancho,alto+ale),irr::video::SColor(250,0,0,0));

        // ///////////////////////////////////////////
        // BUFFER DE TEXTO
        // CONSOLA POR PANTALLA
        // ///////////////////////////////////////////
        auto itC = BUFFER.begin();
        uint16_t DisplayY = 10;
        while (itC!=BUFFER.end()){
            irr::core::stringw WS((*itC).Text.c_str());
            font->draw(WS, irr::core::rect<irr::s32>(20,DisplayY,700,50), irr::video::SColor((*itC).Color.Alpha*255,(*itC).Color.R,(*itC).Color.G,(*itC).Color.B));
            DisplayY += 17;
            ++itC;
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

//////////////////////////////////////////////////////////////////////////////////////
void ScreenConsole::HUD_hability1(ImageHUD &it){
    driver->draw2DRectangle(irr::video::SColor(150,255,0,0),
    irr::core::rect<irr::s32>(it.posx,it.posy,it.posx+it.width,it.posy+it.height*perc));
}

void ScreenConsole::HUD_hability2(ImageHUD &it){
    driver->draw2DRectangle(irr::video::SColor(150,255,0,0),
    irr::core::rect<irr::s32>(it.posx,it.posy,it.posx+it.width,it.posy+it.height*perc2));
}

void ScreenConsole::HUD_hability3(ImageHUD &it){
    driver->draw2DRectangle(irr::video::SColor(150,255,0,0),
    irr::core::rect<irr::s32>(it.posx,it.posy,it.posx+it.width,it.posy+it.height*perc3));
}

void ScreenConsole::HUD_vida(ImageHUD &it){
    driver->draw2DRectangle(irr::video::SColor(150,0,255,0),
    irr::core::rect<irr::s32>(it.posx,it.posy,it.posx+it.width*vida,it.posy+it.height));
}

void ScreenConsole::HUD_arma0(ImageHUD &it){
    std::string hola=std::to_string(balaS)+std::string("/100");
    font->draw(hola.c_str(), irr::core::rect<irr::s32>(it.posx+(it.width/100)*65,it.posy+(it.height/100)*70,700,50), irr::video::SColor(150,255,0,0));
}

void ScreenConsole::HUD_arma1(ImageHUD &it){
    std::string hola=std::to_string(balaP)+std::string("/100");
    font->draw(hola.c_str(), irr::core::rect<irr::s32>(it.posx+(it.width/100)*65,it.posy+(it.height/100)*70,700,50), irr::video::SColor(150,255,0,0));
}
