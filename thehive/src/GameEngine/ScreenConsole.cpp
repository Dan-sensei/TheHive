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

    AddImage("1arma","assets/HUD/ojetecalor.jpg",porc_ancho(70),porc_alto(80),porc_ancho(20),porc_alto(15));//principal
    AddImage("0arma","assets/HUD/ojetecalor.jpg",porc_ancho(75),porc_alto(85),porc_ancho(20),porc_alto(15));

    AddImage("vida","assets/HUD/ojetecalor.jpg",porc_ancho(60),porc_alto(2),porc_ancho(30),porc_alto(3));

    AddImage("G1","assets/HUD/ojetecalor.jpg",porc_ancho(2),porc_alto(2),porc_alto(10),porc_alto(10));
    AddImage("G2","assets/HUD/ojetecalor.jpg",porc_ancho(13),porc_alto(2),porc_alto(10),porc_alto(10));
    AddImage("G3","assets/HUD/ojetecalor.jpg",porc_ancho(24),porc_alto(2),porc_alto(10),porc_alto(10));

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

ScreenConsole::BufferText::BufferText(const std::string &_Text, const gg::Color &_Color)
:Text(_Text), Color(_Color)
{}
ScreenConsole::ImageHUD::ImageHUD(irr::video::ITexture* _texture,float _posx,float _posy,float _width,float _height)
:texture(_texture), posx(_posx),posy(_posy),width(_width),height(_height)
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
            //enableMaterial2D();
            driver->draw2DImage(it->second.texture,
                irr::core::rect<irr::s32>(it->second.posx,it->second.posy,it->second.posx+it->second.width,it->second.posy+it->second.height),
                irr::core::rect<irr::s32>(0,0,it->second.texture->getSize().Width,it->second.texture->getSize().Height)
            );
            //// std::cout << "nombre" <<it->first<< '\n';
            //// std::cout << "posx" <<it->second.posx<< '\n';
            //// std::cout << "posy" <<it->second.posy<< '\n';
            //// std::cout << "tamano H" <<it->second.texture->getSize().Height<< '\n';
            //// std::cout << "tamano W" <<it->second.texture->getSize().Width<< '\n';
            //driver->draw2DRectangle(irr::video::SColor(150,255,0,0),
            //irr::core::rect<irr::s32>(it->second.posx,it->second.posy,it->second.posx+it->second.texture->getSize().Width,it->second.posy+it->second.texture->getSize().Height*perc));
            //irr::core::rect<irr::s32>(it->second.posx,it->second.posy,it->second.posx+it->second.texture->getSize().Width,it->second.posy+it->second.texture->getSize().Height));
            //if(it->first=="hab1"){

            //}
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
            //driver->draw2DRectangle(irr::video::SColor(150,255,0,0),
            std::string hola=std::to_string(balaP)+std::string("/100");
            //irr::core::rect<irr::s32>(it->second.posx,it->second.posy,it->second.posx+it->second.width,it->second.posy+it->second.height*perc3));
            font->draw(hola.c_str(), irr::core::rect<irr::s32>(it->second.posx+(it->second.width/100)*65,it->second.posy+(it->second.height/100)*70,700,50), irr::video::SColor(150,255,0,0));
        }
        if(IMAGE_BUFFER.find("0arma")!=IMAGE_BUFFER.end()){
            it=IMAGE_BUFFER.find("0arma");
            //driver->draw2DRectangle(irr::video::SColor(150,255,0,0),
            //irr::core::rect<irr::s32>(it->second.posx,it->second.posy,it->second.posx+it->second.width,it->second.posy+it->second.height*perc3));
            std::string hola=std::to_string(balaS)+std::string("/100");
            //irr::core::stringw WS((*it).Text.c_str());
            font->draw(hola.c_str(), irr::core::rect<irr::s32>(it->second.posx+(it->second.width/100)*65,it->second.posy+(it->second.height/100)*70,700,50), irr::video::SColor(150,255,0,0));
        }
        //AddImage("G3","assets/HUD/ojetecalor.jpg",porc_ancho(24),porc_alto(2),porc_alto(10),porc_alto(10));
        float ale=porc_alto(2);
        driver->draw2DLine(irr::core::position2d<irr::s32>(ancho-ale,alto),irr::core::position2d<irr::s32>(ancho+ale,alto),irr::video::SColor(250,0,0,0));
        driver->draw2DLine(irr::core::position2d<irr::s32>(ancho,alto-ale),irr::core::position2d<irr::s32>(ancho,alto+ale),irr::video::SColor(250,0,0,0));
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
