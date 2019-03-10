#include "Motor2D.hpp"
#include <iostream>
//#include <SMaterial>
#include <ComponentArch/ObjectManager.hpp>
#include <ComponentArch/Components/CAIEnem.hpp>
#include "SurrealEngine/Imagen2D.hpp"
#include "SurrealEngine/Boton2D.hpp"
#include "SurrealEngine/Cuadrado2D.hpp"
#include "SurrealEngine/Texto2D.hpp"
Motor2D::~Motor2D(){
    CLINMenu();
}
void Motor2D::draw(){

    auto it=TEXT.begin();
    while(it!=TEXT.end()){
        (*it)->Draw();
        it++;
    }
    auto it3=BOTONES.begin();
    while(it3!=BOTONES.end()){
        (*it3)->Draw();
        it3++;
    }
    auto it2 = IMAGENES.begin();
    while(it2!=IMAGENES.end()){
        auto img =it2->second;
        img->Draw();
        it2++;
    }


    //Cuadrado2D boton(0  ,0  ,1    ,1);
    //boton.setColor(glm::vec4(1,0,0,1));
    //boton.Draw();
    //lo mas sencillo
    //Imagen2D img (0,0,1,1,"assets/HUD/Botonsolo.png");
    //img.Draw();
    //std::cout << "dibujando" << '\n';
    //Texto2D nuevo( 0, 0,"Name",glm::vec4(1,0,0,1),30);
    //nuevo.Draw();
    //Texto2D nuevo(0,0.05,"Menu principal",glm::vec4(1,0,0,1),30);
    //nuevo.Draw();

}
Cuadrado2D* Motor2D::addRect(float x, float y,float w, float h){
    auto nuevo =new Cuadrado2D(x,y,w,h);
    RECTANGULOS.push_back(nuevo);
    return nuevo;
}
void Motor2D::prueba(){
    //std::cout << "prueba" << '\n';
    //addText(30,30,"GERMAN GAY",glm::vec4(1,1,0,1),20);
    //AddImage("vida","assets/HUD/Botonsolo.png",0,0,30,30);
    addButton(0,0,30,30,GOPLAY,"assets/HUD/Botonsolo.png","assets/HUD/mongol.jpg","GeMAN",false);
    //std::cout << "end prueba" << '\n';


}
int Motor2D::checkbuton(){
    if(motor->isLClicked()==false){
        return -1;
    }
    std::cout << "pulsado" << '\n';
    double x,y;

    motor->getCursorPosition(x,y);
    auto it=BOTONES.begin();
    while(it!=BOTONES.end()){
        auto but=*it;
        if(but->checkOn(x, y)){
            std::cout << "entra" <<but->getType()<< '\n';
            return but->getType();
        }
        it++;
    }
    return -1;


}
void Motor2D::aplyhover(){
    double x,y;
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
    //auto nuevo = new Imagen2D (0,0,0.5,0.5,"assets/HUD/Botonsolo.png");

    //std::cout << "nuevo " << nuevo << '\n';
    IMAGENES.push_back(std::make_pair(palabra,nuevo));
    //
}
Boton2D* Motor2D::addButton(float x, float y, float w,float h,EnumButtonType id,std::string imagenP,std::string imagenS,std::string texto,bool focus,glm::vec4 _color){
    h=(y+h)/100.0;
    w=(x+w)/100.0;
    x=x/100.0;
    y=y/100.0;
    auto nuevo=new Boton2D(x,y,w,h,id,imagenP,imagenS,texto,focus);
    nuevo->setColor(_color);
    BOTONES.push_back(nuevo);
    return nuevo;

}
void Motor2D::addText(float x, float y,const std::string &Name,glm::vec4 _color,float tam){
    x=x/100.0;
    y=y/100.0;
    auto nuevo=new Texto2D( x, y,Name,_color,tam);
    TEXT.push_back(nuevo);//
}
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


Motor2D::Motor2D(){
    motor = Singleton<SurrealEngine>::Instance();

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


    addButton(45,50,10,9,CONTINUE,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","Continuar",true);
    return 1;

}

//Menu principal
int Motor2D::InitPause(){
    CLINMenu();
    addButton(40,31,20,10,CONTINUE,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","Continuar",true);
    addButton(40,43,20,10,GOOPTIONS,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","Opciones");
    addButton(40,55,20,10,RETURNMENU,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","Salir al menu");


    return 3;

}
//Main Menu
int Motor2D::InitMenu(){
    CLINMenu();
    AddImage("fondo","assets/HUD/menu.png",0,0,100,100);
    //AddStaticTextToBuffer(porc_ancho(45),porc_alto(10),std::string("Menu principal"),gg::Color(0,0,0,1));
    addText(45,10,"Menu principal");

    auto but1=addButton(39,57,7,12,GOPLAY,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","J");
    but1->setSesgo(-0.015);
    but1=addButton(37,70,8,14,GOCREDITS,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","C");
    but1->setSesgo(-0.02);
    but1=addButton(54,57,7,12,GOOPTIONS,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","O");
    but1->setSesgo(0.015);
    but1=addButton(55,70,8,14,CLOSE,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","S");
    but1->setSesgo(0.02);
    return 4;
}
//Jugar
int Motor2D::InitMenu2(){
    CLINMenu();
    AddImage("fondo","assets/HUD/menucerca.png",0,0,100,100);

    addText(45,10,"Play");
    //AddStaticTextToBuffer(porc_ancho(45),porc_alto(10),std::string("Play"),gg::Color(0,0,0,1));
    addButton(40,21,20,10,DIFF1,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","Larva",true);
    addButton(40,33,20,10,DIFF2,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","Alien");
    addButton(40,45,20,10,DIFF3,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","The hive");
    addButton(30,60,40,20,START,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","Play");

    addButton(20,20,5,9,GOMAIN,"assets/HUD/Botonsoloatras.png","assets/HUD/Botonsoloatras.png","");
return 5;
}
//Creditos
int Motor2D::InitMenu3(){
    CLINMenu();
    AddImage("fondo","assets/HUD/menucerca.png",0,0,100,100);

    addText(45,10,"Credits");

    //AddStaticTextToBuffer(porc_ancho(45),porc_alto(10),std::string("Credits"),gg::Color(0,0,0,1));

    addButton(20,20,5,9,GOMAIN,"assets/HUD/Botonsoloatras.png","assets/HUD/Botonsoloatras.png","");

    return 1;
}
//Opciones
int Motor2D::InitMenu4(){
    CLINMenu();
    AddImage("fondo","assets/HUD/menucerca.png",0,0,100,100);

    addText(45,10,"Options");

    //AddStaticTextToBuffer(porc_ancho(45),porc_alto(10),std::string("Options"),gg::Color(0,0,0,1));

    addButton(40,31,20,10,GOVIDEO,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","Graphics");
    addButton(40,43,20,10,GOMUSIC,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","Audio");
    addButton(40,55,20,10,GOCONTROLLS,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","Controlls");

    addButton(20,20,5,9,CONTINUE,"assets/HUD/Botonsoloatras.png","assets/HUD/Botonsoloatras.png","");

    return 4;
}
//graficos
int Motor2D::InitMenu5(){
    CLINMenu();
    AddImage("fondo","assets/HUD/menucerca.png",0,0,100,100);

    addText(45,10,"Video");
    //AddStaticTextToBuffer(porc_ancho(45),porc_alto(10),std::string("Video"),gg::Color(0,0,0,1));
    addButton(20,20,5,9,GOINITOPTIONS,"assets/HUD/Botonsoloatras.png","assets/HUD/Botonsoloatras.png","");

    return 1;
}
//sonido
int Motor2D::InitMenu6(){
    CLINMenu();

    AddImage("fondo","assets/HUD/menucerca.png",0,0,100,100);




    addText(45,10,"Audio"    );
    addText(30,51,"Dialogues"    );
    addText(40,51,""+VolDialogo );

    //AddStaticTextToBuffer(porc_ancho(45),porc_alto(10),std::string("Audio"),gg::Color(0,0,0,1));
    //AddStaticTextToBuffer(porc_ancho(30),porc_alto(51),std::string("Dialogues"),gg::Color(0,0,0,1));
    //AddStaticTextToBuffer(porc_ancho(40),porc_alto(51),std::to_string(VolDialogo),gg::Color(0,0,0,1));
    addButton(50,50,2,5,MOREDIALOD,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","M");
    addButton(53,50,2,5,LESSDIALOD,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","m");
    std::cout << VolMusic << '\n';
    addText(30,57,"Music"  );
    addText(40,57,""+VolMusic);
    //AddStaticTextToBuffer(porc_ancho(30),porc_alto(57),std::string("Music"),gg::Color(0,0,0,1));
    //AddStaticTextToBuffer(porc_ancho(40),porc_alto(57),std::to_string(VolMusic),gg::Color(0,0,0,1));
    addButton(50,56,2,5,MOREMUSIC,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","M");
    addButton(53,56,2,5,LESSMUSIC,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","m");
    addText(30,63,"Effects"    );
    addText(40,63,""+VolEffect  );
    //AddStaticTextToBuffer(porc_ancho(30),porc_alto(63),std::string("Effects"),gg::Color(0,0,0,1));
    //AddStaticTextToBuffer(porc_ancho(40),porc_alto(63),std::to_string(VolEffect),gg::Color(0,0,0,1));
    addButton(50,62,2,5,MOREEFFECT,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","M");
    addButton(53,62,2,5,LESSEFFECT,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","m");

    addButton(20,20,5,9,GOINITOPTIONS,"assets/HUD/Botonsoloatras.png","assets/HUD/Botonsoloatras.png","");

    return 7;
}
//controles
int Motor2D::InitMenu7(){
    CLINMenu();
    AddImage("fondo","assets/HUD/menucerca.png",0,0,100,100);

    //AddStaticTextToBuffer(porc_ancho(45),porc_alto(10),std::string("Controlls"),gg::Color(0,0,0,1));
    addText(45,10,"Controlls");

    addButton(20,20,5,9,GOINITOPTIONS,"assets/HUD/Botonsoloatras.png","assets/HUD/Botonsoloatras.png","");

    return 1;
}


void Motor2D::InitHUD(){


    AddImage("hab1","assets/HUD/hab1.png",  2, 90,7,10);
    auto boton=addRect(                     2, 90,7,10);
    boton->setColor(glm::vec4(1,1,1,0.25));


    AddImage("hab2","assets/HUD/hab2.png",  12, 90,7,10);
    boton=addRect(                          12, 90,7,10);
    boton->setColor(glm::vec4(1,1,1,0.25));


    AddImage("hab3","assets/HUD/hab3.png",  22,90,7,10);
    boton=addRect(                          22,90,7,10);
    boton->setColor(glm::vec4(1,1,1,0.25));


    float _x,_y,x,y,w,h;
    x=75;
    y=85;
    w=20;
    h=15;
    _x= x+w*0.5;
    _y= y+h*0.5;
    AddImage("0arma","assets/HUD/cf_hud_d.jpg",75,85,20,15);
    addText(_x, _y,"arma0",glm::vec4(1,1,1,1),30);
    x=70;
    y=80;
    w=20;
    h=15;
    _x= x+w*0.5;
    _y= y+h*0.5;
    AddImage("1arma","assets/HUD/cf_hud_b.jpg",70,80,20,15); // Principal
    addText(_x, _y,"arma1",glm::vec4(1,1,1,1),30);


    AddImage("vida","assets/HUD/Vida.png",  60,2,35,7);
    boton=addRect(                          60,2,35,7);
    boton->setColor(glm::vec4(0,1,0,0.6));


    //AddImage("G1","assets/HUD/Botonsolo.png",porc_ancho(2),porc_alto(2),porc_alto(10),porc_alto(10));
    //AddImage("G2","assets/HUD/Botonsolo.png",porc_ancho(13),porc_alto(2),porc_alto(10),porc_alto(10));
    //AddImage("G3","assets/HUD/Botonsolo.png",porc_ancho(24),porc_alto(2),porc_alto(10),porc_alto(10));

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

void Motor2D::CLINMenu(){
    //liberar eso
    //std::vector<Cuadrado2D*> RECTANGULOS;
    //std::vector<Boton2D*> BOTONES;
    //std::vector<Boton2D*> TEXT;
    auto it = IMAGENES.begin();
    while(it!=IMAGENES.end()){
        delete it->second;
        it++;
    }
    IMAGENES.clear();

    auto it2=TEXT.begin();
    while(it2!=TEXT.end()){
        delete (*it2);
        it2++;
    }
    TEXT.clear();

    auto it3=BOTONES.begin();
    while(it3!=BOTONES.end()){
        delete (*it3);
        it3++;
    }
    BOTONES.clear();

    auto it4=RECTANGULOS.begin();
    while(it4!=RECTANGULOS.end()){
        delete (*it4);
        it4++;
    }
    RECTANGULOS.clear();





}
void Motor2D::CLINNormal(){
    //liberar eso
    //std::vector<Cuadrado2D*> RECTANGULOS;
    //std::vector<Boton2D*> BOTONES;
    //std::vector<Boton2D*> TEXT;
    auto it = IMAGENES.begin();
    while(it!=IMAGENES.end()){
        delete it->second;
        it++;
    }
    IMAGENES.clear();



}

void Motor2D::DisplayHUD(){
    if(true){
        auto it = IMAGENES.begin();
        float X,Y,H,W,T_W,T_H;
        while(it!=IMAGENES.end()){
            auto img =it->second;
            if(mapHudFunctions.find(it->first) != mapHudFunctions.end())
                (this->*mapHudFunctions[it->first])(img);

                img->Draw();
            it++;
        }
        //
        //AddImage("G3","assets/HUD/Botonsolo.png",porc_ancho(24),porc_alto(2),porc_alto(10),porc_alto(10));
        //float ale=porc_alto(2);
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

    RECTANGULOS[0]->setPos(x, y, w, y+(h-y)*perc);
    RECTANGULOS[0]->Draw();
}

void Motor2D::HUD_hability2(Imagen2D *it){
    float x,y,w,h;
    x=it->getX();
    y=it->getY();
    w=it->getW();
    h=it->getH();

    RECTANGULOS[1]->setPos(x, y, w, y+(h-y)*perc2);
    RECTANGULOS[1]->Draw();
}

void Motor2D::HUD_hability3(Imagen2D *it){
    float x,y,w,h;
    x=it->getX();
    y=it->getY();
    w=it->getW();
    h=it->getH();
    RECTANGULOS[2]->setPos(x, y, w, y+(h-y)*perc3);
    RECTANGULOS[2]->Draw();
}

void Motor2D::HUD_vida(Imagen2D *it){
    float x,y,w,h;
    x=it->getX();
    y=it->getY();
    w=it->getW();
    h=it->getH();


    //Cuadrado2D boton(0 ,0  ,1  ,1);
    RECTANGULOS[3]->setPos(x, y, x+(w-x)*vida , h);
    RECTANGULOS[3]->Draw();
}
//necesitamos escribir por pantalla
void Motor2D::HUD_arma0(Imagen2D *it){

    std::string hola=std::to_string(balaS)+"/"+std::to_string(balaS_TOT);
    TEXT[0]->setText(hola);
    TEXT[0]->Draw();
}

void Motor2D::HUD_arma1(Imagen2D *it){
    std::string hola=std::to_string(balaP)+"/"+std::to_string(balaP_TOT);
    TEXT[1]->setText(hola);
    TEXT[1]->Draw();
}


void gg::cout (const std::string &Text, const gg::Color &color){
    //Singleton<Motor2D>::Instance()->AddTextToBuffer(Text, color);
}
void gg::cout (const glm::vec3 &Vector, const gg::Color &color){
    //std::string VectorString = "(" + std::to_string(Vector.x) + "," + std::to_string(Vector.y) + "," + std::to_string(Vector.z) + ")";
    //Singleton<Motor2D>::Instance()->AddTextToBuffer(VectorString, color);
}
