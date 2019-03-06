#include "Motor2D.hpp"
#include <iostream>
//#include <SMaterial>
#include <ComponentArch/ObjectManager.hpp>
#include <ComponentArch/Components/CAIEnem.hpp>
void Motor2D::draw(){

    auto it=TEXT.begin();
    while(it!=TEXT.end()){
        (*it)->Draw();
        it++;
    }

    auto it2 = IMAGENES.begin();
    while(it2!=IMAGENES.end()){
        auto img =it2->second;
        img->Draw();
        it2++;
    }
    auto it3=BOTONES.begin();
    while(it3!=BOTONES.end()){
        (*it3)->Draw();
        it3++;
    }
    //Cuadrado2D boton(0  ,0  ,1    ,1);
    //boton.setColor(glm::vec4(1,0,0,1));
    //boton.Draw();

    // Imagen2D img (0,0,1,1,"assets/HUD/ojetecalor.jpg");
    // img.Draw();
    //std::cout << "dibujando" << '\n';
    //Texto2D nuevo( 0, 0,"Name",glm::vec4(1,0,0,1),30);
    //nuevo.Draw();

}
void Motor2D::prueba(){
    //std::cout << "prueba" << '\n';
    //addText(30,30,"GERMAN GAY",glm::vec4(1,1,0,1),20);
    //AddImage("vida","assets/HUD/ojetecalor.jpg",0,0,30,30);
    addButton(0,0,30,30,GOPLAY,"assets/HUD/ojetecalor.jpg","assets/HUD/mongol.jpg","GeMAN",false);
    //std::cout << "end prueba" << '\n';


}
void Motor2D::checkbuton(){
    double x,y;
    motor->isLClickPressed();
    motor->getCursorPosition(x,y);
    auto it=BOTONES.begin();
    while(it!=BOTONES.end()){
        auto but=*it;
        if(but->checkOn(x, y)){
            //std::cout << "encima" << '\n';
            //setImage
            but->hover(true);
        }
        else{

            but->hover(false);
        }
        it++;
    }


}
void Motor2D::AddImage(std::string palabra,std::string source,float _posx,float _posy,float _width,float _height){
    float x,y,w,h;
    x=_posx/100.0;
    y=_posy/100.0;
    w=(_posx+_width)/100.0;
    h=(_posy+_height)/100.0;
    auto nuevo = new Imagen2D(x,y,w,h,source);
    //auto nuevo = new Imagen2D (0,0,0.5,0.5,"assets/HUD/ojetecalor.jpg");

    std::cout << "nuevo " << nuevo << '\n';
    IMAGENES.push_back(std::make_pair(palabra,nuevo));
    //
}
void Motor2D::addButton(float x, float y, float w,float h,EnumButtonType id,std::string imagenP,std::string imagenS,std::string texto,bool focus){
    h=(y+h)/100.0;
    w=(x+w)/100.0;
    x=x/100.0;
    y=y/100.0;
    auto nuevo=new Boton2D(x,y,w,h,id,imagenP,imagenS,texto,focus);
    BOTONES.push_back(nuevo);
}
void Motor2D::addText(float x, float y,const std::string &Name,glm::vec4 _color,float tam){
    x=x/100.0;
    y=y/100.0;
    auto nuevo=new Texto2D( x, y,Name,_color,tam);
    TEXT.push_back(nuevo);
}
irr::IrrlichtDevice* Motor2D::IrrlichtDevice = nullptr;
void Motor2D::setprogress(int hab,float prog){
    if(hab==0){
        perc=1-prog;

    }else if(hab==1){
        perc2=1-prog;

    }
    else{
        perc3=1-prog;

    }
}

void Motor2D::setvida(float _vida){
    // std::cout << "hacemos algo" << '\n';
    vida=_vida;
}
void Motor2D::setVolDialogo(int _vol){
VolDialogo=_vol;
}
void Motor2D::setVolEffect(int _vol){
VolEffect=_vol;
}
void Motor2D::setVolMusic(int _vol){
VolMusic=_vol;
}
void Motor2D::setbullet(int tipo,int b_act, int b_tot){
    if(tipo==0){
        balaP       = b_act;
        balaP_TOT   = b_tot;

    }else {
        balaS       = b_act;
        balaS_TOT   = b_tot;
    }
}

float Motor2D::porc_alto(float x){
    return ((alto*2)/100.0)*x;
}
float Motor2D::porc_ancho(float x){
    return ((ancho*2)/100.0)*x;
}
Motor2D::Motor2D(){
    motor = Singleton<TMotorTAG>::Instance();

    //font = IrrlichtDevice->getGUIEnvironment()->getFont("assets/Fonts/Debug.png");
    //irr::video::IVideoDriver* driver = IrrlichtDevice->getVideoDriver();

    //ancho=(driver->getScreenSize().Width/2);
    //alto=(driver->getScreenSize().Height/2);
}
std::string  Motor2D::BoolToString(bool b)
{
  if(b){
     return  std::string("true");
  }
  else{
      return std::string("false");
  }
}
int Motor2D::InitAIDebug(int id){
    CLINMenu();
    ObjectManager* Manager = Singleton<ObjectManager>::Instance();
    // std::cout << "id:" <<id<< '\n';
    CAIEnem* AIEnem = static_cast<CAIEnem*>(Manager->getComponent(gg::AIENEM,id));
    CVida* Vida = static_cast<CVida*>(Manager->getComponent(gg::VIDA,id));


    std::string tipo;

    switch (AIEnem->getEnemyType()) {
        case gg::SOLDIER:
            tipo="SOLDIER";
            break;
        case gg::TANK:
            tipo="TANK";
            break;
        case gg::RUSHER:
            tipo="RUSHER";
            break;
        case gg::SWARM:
            tipo="SWARM";
            break;
        case gg::TRACKER:
            break;
    }
    addText(45, 10,"Debug Enemigo");

    addText(10, 10,"Tipo de enemigo:"  +tipo , glm::vec4(1,0,0,1));

    addText(10,15,"Vida:"                              +std::to_string(Vida->getVida()                      ),glm::vec4(1,0,0,1));

    addText(10,20,"Estoy viendo al jugador:"           +BoolToString(AIEnem->playerSeeing                   ),glm::vec4(1,0,0,1));
    addText(10,25,"He visto al jugador:"               +BoolToString(AIEnem->playerSeen                     ),glm::vec4(1,0,0,1));
    addText(10,30,"Estoy afectado por ultrasonido:"    +BoolToString(AIEnem->ultrasonido                    ),glm::vec4(1,0,0,1));
    addText(10,35,"Estoy afectado por senyuelo:"       +BoolToString(AIEnem->senyuelo                       ),glm::vec4(1,0,0,1));
    addText(10,40,"Jugador a rango:"                   +BoolToString(AIEnem->playerOnRange                  ),glm::vec4(1,0,0,1));
    addText(10,45,"Puedo atacar:"                      +BoolToString(AIEnem->getImAttacking()               ),glm::vec4(1,0,0,1));
    addText(10,50,"Acaba de morir un aliado cercano:"  +BoolToString(AIEnem->getCloserAllyIsDead()          ),glm::vec4(1,0,0,1));
    addText(10,55,"Me esta atacando el jugador:"       +BoolToString(AIEnem->getPlayerIsAttacking()         ),glm::vec4(1,0,0,1));

    addText(10,60,"Rango de vision:"                   +std::to_string(AIEnem->Vrange                       ),glm::vec4(1,0,0,1));
    addText(10,65,"Rango de ataque:"                   +std::to_string(AIEnem->Arange                       ),glm::vec4(1,0,0,1));
    addText(10,70,"Enfado:"                            +std::to_string(AIEnem->getRage()                    ),glm::vec4(1,0,0,1));

    addText(10,75,"Tarea actual:"                      +std::to_string(AIEnem->arbol->taskactual()          ),glm::vec4(1,0,0,1));




/*
    AddStaticTextToBuffer(porc_ancho(45),porc_alto(10),std::string("Debug Enemigo"),gg::Color(0,0,0,1));

    AddStaticTextToBuffer(porc_ancho(10),porc_alto(10),std::string("Tipo de enemigo:"                              +tipo                      ),gg::Color(255,0,0,1));

    AddStaticTextToBuffer(porc_ancho(10),porc_alto(15),std::string("Vida:"                              +std::to_string(Vida->getVida()                      )),gg::Color(255,0,0,1));

    AddStaticTextToBuffer(porc_ancho(10),porc_alto(20),std::string("Estoy viendo al jugador:"           +BoolToString(AIEnem->playerSeeing              )),gg::Color(255,0,0,1));
    AddStaticTextToBuffer(porc_ancho(10),porc_alto(25),std::string("He visto al jugador:"               +BoolToString(AIEnem->playerSeen                )),gg::Color(255,0,0,1));
    AddStaticTextToBuffer(porc_ancho(10),porc_alto(30),std::string("Estoy afectado por ultrasonido:"    +BoolToString(AIEnem->ultrasonido               )),gg::Color(255,0,0,1));
    AddStaticTextToBuffer(porc_ancho(10),porc_alto(35),std::string("Estoy afectado por senyuelo:"       +BoolToString(AIEnem->senyuelo                  )),gg::Color(255,0,0,1));
    AddStaticTextToBuffer(porc_ancho(10),porc_alto(40),std::string("Jugador a rango:"                   +BoolToString(AIEnem->playerOnRange             )),gg::Color(255,0,0,1));
    AddStaticTextToBuffer(porc_ancho(10),porc_alto(45),std::string("Puedo atacar:"                      +BoolToString(AIEnem->getImAttacking()          )),gg::Color(255,0,0,1));
    AddStaticTextToBuffer(porc_ancho(10),porc_alto(50),std::string("Acaba de morir un aliado cercano:"  +BoolToString(AIEnem->getCloserAllyIsDead()     )),gg::Color(255,0,0,1));
    AddStaticTextToBuffer(porc_ancho(10),porc_alto(55),std::string("Me esta atacando el jugador:"       +BoolToString(AIEnem->getPlayerIsAttacking()    )),gg::Color(255,0,0,1));

    AddStaticTextToBuffer(porc_ancho(10),porc_alto(60),std::string("Rango de vision:"                   +std::to_string(AIEnem->Vrange                    )),gg::Color(255,0,0,1));
    AddStaticTextToBuffer(porc_ancho(10),porc_alto(65),std::string("Rango de ataque:"                   +std::to_string(AIEnem->Arange                    )),gg::Color(255,0,0,1));
    AddStaticTextToBuffer(porc_ancho(10),porc_alto(70),std::string("Enfado:"                            +std::to_string(AIEnem->getRage()                 )),gg::Color(255,0,0,1));

    AddStaticTextToBuffer(porc_ancho(10),porc_alto(75),std::string("Tarea actual:"                      +std::to_string(AIEnem->arbol->taskactual()       )),gg::Color(255,0,0,1));
*/

    //ObjectManager* Manager = Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, pRec->idSource);


    addButton(45,50,55,59,CONTINUE,"imagenP","imagenS","Continuar",true);
    return 1;

}

//Menu principal
int Motor2D::InitPause(){
    CLINMenu();
    addButton(45,50,55,59,CONTINUE,"imagenP","imagenS","Continuar",true);
    addButton(45,60,55,69,GOOPTIONS,"imagenP","imagenS","Opciones");
    addButton(45,70,55,79,RETURNMENU,"imagenP","imagenS","Salir al menu");
    return 3;

}
//Main Menu
int Motor2D::InitMenu(){
    CLINMenu();
    //AddStaticTextToBuffer(porc_ancho(45),porc_alto(10),std::string("Menu principal"),gg::Color(0,0,0,1));
    addText(45,10,"Menu principal");

    addButton(38,50,48,70,GOPLAY,"imagenP","imagenS","J");
    addButton(38,75,48,95,GOCREDITS,"imagenP","imagenS","C");
    addButton(52,50,62,70,GOOPTIONS,"imagenP","imagenS","O");
    addButton(52,75,62,95,CLOSE,"imagenP","imagenS","S");
    return 4;
}
//Jugar
int Motor2D::InitMenu2(){
    CLINMenu();
    addText(45,10,"Play");
    //AddStaticTextToBuffer(porc_ancho(45),porc_alto(10),std::string("Play"),gg::Color(0,0,0,1));
    addButton(45,50,55,59,DIFF1,"imagenP","imagenS","Larva",true);
    addButton(45,60,55,69,DIFF2,"imagenP","imagenS","Alien");
    addButton(45,70,55,79,DIFF3,"imagenP","imagenS","The hive");
    addButton(40,80,60,89,START,"imagenP","imagenS","Play");

    addButton(65,80,70,89,GOMAIN,"imagenP","imagenS","Back");
return 5;
}
//Creditos
int Motor2D::InitMenu3(){
    CLINMenu();
    addText(45,10,"Credits");

    //AddStaticTextToBuffer(porc_ancho(45),porc_alto(10),std::string("Credits"),gg::Color(0,0,0,1));

    addButton(65,80,70,89,GOMAIN,"imagenP","imagenS","Back");
    return 1;
}
//Opciones
int Motor2D::InitMenu4(){
    CLINMenu();
    addText(45,10,"Options");

    //AddStaticTextToBuffer(porc_ancho(45),porc_alto(10),std::string("Options"),gg::Color(0,0,0,1));

    addButton(45,50,55,59,GOVIDEO,"imagenP","imagenS","Graphics");
    addButton(45,60,55,69,GOMUSIC,"imagenP","imagenS","Audio");
    addButton(45,70,55,79,GOCONTROLLS,"imagenP","imagenS","Controlls");

    addButton(65,80,70,89,CONTINUE,"imagenP","imagenS","Back");
    return 4;
}
//graficos
int Motor2D::InitMenu5(){
    CLINMenu();
    addText(45,10,"Video");
    //AddStaticTextToBuffer(porc_ancho(45),porc_alto(10),std::string("Video"),gg::Color(0,0,0,1));

    addButton(65,80,70,89,GOINITOPTIONS,"imagenP","imagenS","Back");
    return 1;
}
//sonido
int Motor2D::InitMenu6(){
    CLINMenu();



    addText(45,10,"Audio"    );
    addText(30,51,"Dialogues"    );
    addText(40,51,""+VolDialogo );

    //AddStaticTextToBuffer(porc_ancho(45),porc_alto(10),std::string("Audio"),gg::Color(0,0,0,1));
    //AddStaticTextToBuffer(porc_ancho(30),porc_alto(51),std::string("Dialogues"),gg::Color(0,0,0,1));
    //AddStaticTextToBuffer(porc_ancho(40),porc_alto(51),std::to_string(VolDialogo),gg::Color(0,0,0,1));
    addButton(50,50,52,55,MOREDIALOD,"imagenP","imagenS","+");
    addButton(53,50,55,55,LESSDIALOD,"imagenP","imagenS","-");
    addText(30,57,"Music"    );
    addText(40,57,""+VolMusic);
    //AddStaticTextToBuffer(porc_ancho(30),porc_alto(57),std::string("Music"),gg::Color(0,0,0,1));
    //AddStaticTextToBuffer(porc_ancho(40),porc_alto(57),std::to_string(VolMusic),gg::Color(0,0,0,1));
    addButton(50,56,52,61,MOREMUSIC,"imagenP","imagenS","+");
    addButton(53,56,55,61,LESSMUSIC,"imagenP","imagenS","-");
    addText(30,63,"Effects"    );
    addText(40,63,""+VolEffect  );
    //AddStaticTextToBuffer(porc_ancho(30),porc_alto(63),std::string("Effects"),gg::Color(0,0,0,1));
    //AddStaticTextToBuffer(porc_ancho(40),porc_alto(63),std::to_string(VolEffect),gg::Color(0,0,0,1));
    addButton(50,62,52,67,MOREEFFECT,"imagenP","imagenS","+");
    addButton(53,62,55,67,LESSEFFECT,"imagenP","imagenS","-");
    addButton(65,80,70,89,GOINITOPTIONS,"imagenP","imagenS","Back");
    return 7;
}
//controles
int Motor2D::InitMenu7(){
    CLINMenu();
    //AddStaticTextToBuffer(porc_ancho(45),porc_alto(10),std::string("Controlls"),gg::Color(0,0,0,1));
    addText(45,10,"Controlls");

    addButton(65,80,70,89,GOINITOPTIONS,"imagenP","imagenS","Back");
    return 1;
}

int Motor2D::Pulsarboton(int but){
    return Botones.at(but)->getID();
}
void Motor2D::InitHUD(){


    AddImage("hab1","assets/HUD/hab1.png",2, 90,10,10);
    AddImage("hab2","assets/HUD/hab2.png",12, 90,10,10);
    AddImage("hab3","assets/HUD/hab3.png",22,90,10,10);

    AddImage("0arma","assets/HUD/cf_hud_d.jpg",75,85,20,15);
    AddImage("1arma","assets/HUD/cf_hud_b.jpg",70,80,20,15); // Principal

    AddImage("vida","assets/HUD/cf_hud_d.jpg",60,2,30,3);

    //AddImage("G1","assets/HUD/ojetecalor.jpg",porc_ancho(2),porc_alto(2),porc_alto(10),porc_alto(10));
    //AddImage("G2","assets/HUD/ojetecalor.jpg",porc_ancho(13),porc_alto(2),porc_alto(10),porc_alto(10));
    //AddImage("G3","assets/HUD/ojetecalor.jpg",porc_ancho(24),porc_alto(2),porc_alto(10),porc_alto(10));

    // MAPA A FUNCIONES MOLON
    mapHudFunctions.insert(std::make_pair("hab1",&Motor2D::HUD_hability1));
    mapHudFunctions.insert(std::make_pair("hab2",&Motor2D::HUD_hability2));
    mapHudFunctions.insert(std::make_pair("hab3",&Motor2D::HUD_hability3));
    mapHudFunctions.insert(std::make_pair("vida",&Motor2D::HUD_vida));
    mapHudFunctions.insert(std::make_pair("0arma",&Motor2D::HUD_arma0));
    mapHudFunctions.insert(std::make_pair("1arma",&Motor2D::HUD_arma1));

    perc        =   0;
    perc2       =   0;
    perc3       =   0;
    balaP       =   0;
    balaS       =   0;
    vida        =   1;
    VolDialogo  =   50;
    VolEffect   =   50;
    VolMusic    =   50;

}



//void Motor2D::AddTextToBuffer(const std::string &Text, const gg::Color &color){
//    if(BUFFER.size()>35)
//        BUFFER.pop_front();

//    BUFFER.emplace_back(Text, color);
//}
//void Motor2D::AddStaticTextToBuffer(int x,int y, std::string Text,  gg::Color color){
//    TEXT_BUFFER.emplace_back(x,y,Text, color);
//}
Motor2D::BufferText::BufferText(const std::string &_Text, const gg::Color &_Color)
:Text(_Text), Color(_Color)
{}
Motor2D::StaticText::StaticText(float _x,float _y, std::string _Text,gg::Color _Color)
:Text(_Text),Color(_Color),posx(_x),posy(_y)
{}
void Motor2D::CLINMenu(){
    //liberar eso
    //std::vector<Cuadrado2D*> RECTANGULOS;
    //std::vector<Boton2D*> BOTONES;
    //std::vector<Boton2D*> TEXT;



}
void Motor2D::CLINNormal(){
    //liberar eso
    //std::vector<Cuadrado2D*> RECTANGULOS;
    //std::vector<Boton2D*> BOTONES;
    //std::vector<Boton2D*> TEXT;
    auto it = IMAGENES.begin();
    float X,Y,H,W,T_W,T_H;
    while(it!=IMAGENES.end()){
        delete it->second;
        it++;
    }
    IMAGENES.clear();



}
//void Motor2D::DisplayDebug(){
//    if(true){
//        auto it = BUFFER.begin();
//        uint16_t DiplayY = 10;
//        while (it!=BUFFER.end()){
//            irr::core::stringw WS((*it).Text.c_str());
//            font->draw(WS, irr::core::rect<irr::s32>(20,DiplayY,700,50), irr::video::SColor((*it).Color.Alpha*255,(*it).Color.R,(*it).Color.G,(*it).Color.B));
//            DiplayY += 17;
//            ++it;
//        }
//    }
//}
void Motor2D::DisplayMenu(){
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
void Motor2D::DisplayHUD(){
    if(true){
        //irr::video::ITexture* images = driver->getTexture("assets/HUD/ojetecalor.jpg");
        //driver->draw2DImage(images, irr::core::position2d<irr::s32>(50,50),
        //irr::core::rect<irr::s32>(0,0,342,224), 0,
        //irr::video::SColor(255,255,255,255), true);
        //driver->draw2DImage(images, irr::core::position2d<irr::s32>(50,50));

        auto it = IMAGENES.begin();
        float X,Y,H,W,T_W,T_H;
        while(it!=IMAGENES.end()){
            auto img =it->second;
            img->Draw();
            if(mapHudFunctions.find(it->first) != mapHudFunctions.end())
                (this->*mapHudFunctions[it->first])(img);

            it++;
        }
        //
        //AddImage("G3","assets/HUD/ojetecalor.jpg",porc_ancho(24),porc_alto(2),porc_alto(10),porc_alto(10));
        float ale=porc_alto(2);
        Cuadrado2D horizontal(-0.1  ,0  ,0.1    ,0.001);
        Cuadrado2D vertical(0  ,-0.1  ,0.001    ,0.1);


    }
}
float getX();
float getW();
float getY();
float getH();
//////////////////////////////////////////////////////////////////////////////////////
void Motor2D::HUD_hability1(Imagen2D *it){
    float x,y,w,h;
    x=it->getX();
    y=it->getY();
    w=it->getW();
    h=it->getH();

    Cuadrado2D boton(x  ,y  ,x+w    ,y+h*perc);
    boton.setColor(glm::vec4(1,1,1,0.25));



    boton.Draw();
}

void Motor2D::HUD_hability2(Imagen2D *it){
    float x,y,w,h;
    x=it->getX();
    y=it->getY();
    w=it->getW();
    h=it->getH();

    Cuadrado2D boton(x  ,y  ,x+w    ,y+h*perc2);
    boton.setColor(glm::vec4(1,1,1,0.25));



    boton.Draw();
}

void Motor2D::HUD_hability3(Imagen2D *it){
    float x,y,w,h;
    x=it->getX();
    y=it->getY();
    w=it->getW();
    h=it->getH();

    Cuadrado2D boton(x  ,y  ,x+w    ,y+h*perc3);
    boton.setColor(glm::vec4(1,1,1,0.25));

    boton.Draw();
}

void Motor2D::HUD_vida(Imagen2D *it){
    float x,y,w,h;
    x=it->getX();
    y=it->getY();
    w=it->getW();
    h=it->getH();


    Cuadrado2D boton(x  ,y  ,x+w*vida    ,y+h);
    boton.setColor(glm::vec4(0,1,0,0.6));

    boton.Draw();
}
//necesitamos escribir por pantalla
void Motor2D::HUD_arma0(Imagen2D *it){

    //hace falta lo de los botones aqui
    //std::string hola=std::to_string(balaS)+"/"+std::to_string(balaS_TOT);
    //font->draw(hola.c_str(), irr::core::rect<irr::s32>(it.posx+(it.width/100)*65,it.posy+(it.height/100)*70,700,50), irr::video::SColor(255,255,255,255));
}

void Motor2D::HUD_arma1(Imagen2D *it){
    //std::string hola=std::to_string(balaP)+"/"+std::to_string(balaP_TOT);
    //font->draw(hola.c_str(), irr::core::rect<irr::s32>(it.posx+(it.width/100)*65,it.posy+(it.height/100)*70,700,50), irr::video::SColor(255,255,255,255));
}
