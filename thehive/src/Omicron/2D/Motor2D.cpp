#include "Motor2D.hpp"

#include <ComponentArch/ObjectManager.hpp>
#include <ComponentArch/Components/CAIEnem.hpp>
#include <Omicron/2D/Imagen2D.hpp>
#include <Omicron/2D/Boton2D.hpp>
#include <Omicron/2D/Cuadrado2D.hpp>
#include <Omicron/2D/Texto2D.hpp>
#include <ComponentArch/Components/CVida.hpp>
/*
std::string imgarmaP;
std::string imgarmaS;
*/
Motor2D::Motor2D():POUP(nullptr){
    motor = Singleton<Omicron>::Instance();
    pop=false;
    //font = IrrlichtDevice->getGUIEnvironment()->getFont("assets/Fonts/Debug.png");
    //irr::video::IVideoDriver* driver = IrrlichtDevice->getVideoDriver();

    //ancho=(driver->getScreenSize().Width/2);
    //alto=(driver->getScreenSize().Height/2);

    SS = Singleton<SoundSystem>::Instance();

    s_hover = new SonidoNormal();
    SS->createSound("event:/SFX/Menu/Seleccionar",s_hover);
    muteEffect = false;
    muteMusic = false;
    muteDialog = false;
    BOTONES.reserve(10);
}


Motor2D::~Motor2D(){
    //delete s_hover;
    CLINMenu();
}

void Motor2D::colorMute(EnumButtonType tipo){
    // auto it=BOTONES.begin();
    // while(it!=BOTONES.end()){
    //     if((*it)->getType() == tipo){
    //         if (tipo == MUTEEFFECT){
    //             if(muteEffect==true){
    //                 (*it)->setColorInicial(glm::vec4 (0,0,0,1));
    //                 (*it)->setColor(glm::vec4 (0,0,0,1));
    //                 muteEffect = false;
    //             }
    //             else{
    //                 (*it)->setColorInicial(glm::vec4 (1,0,0,1));
    //                 (*it)->setColor(glm::vec4 (1,0,0,1));
    //                 muteEffect = true;
    //             }
    //         }
    //
    //         if (tipo == MUTEMUSIC){
    //             if(muteMusic==true){
    //                 (*it)->setColorInicial(glm::vec4 (0,0,0,1));
    //                 (*it)->setColor(glm::vec4 (0,0,0,1));
    //                 muteMusic = false;
    //             }
    //             else{
    //                 (*it)->setColorInicial(glm::vec4 (1,0,0,1));
    //                 (*it)->setColor(glm::vec4 (1,0,0,1));
    //                 muteMusic = true;
    //             }
    //         }
    //
    //         if (tipo == MUTEDIALOD){
    //             if(muteDialog==true){
    //                 (*it)->setColorInicial(glm::vec4 (0,0,0,1));
    //                 (*it)->setColor(glm::vec4 (0,0,0,1));
    //                 muteDialog = false;
    //             }
    //             else{
    //                 (*it)->setColorInicial(glm::vec4 (1,0,0,1));
    //                 (*it)->setColor(glm::vec4 (1,0,0,1));
    //                 muteDialog = true;
    //             }
    //         }
    //
    //
    //     }
    //     it++;
    // }
}

void Motor2D::draw(){

    // auto it=TEXT.begin();
    // while(it!=TEXT.end()){
    //     (*it)->Draw();
    //     it++;
    // }
    // std::cout << "BOTONES SIZE " << BOTONES.size() << '\n';
    auto it1=RECTANGULOS.begin();
    while(it1!=RECTANGULOS.end()){
        it1->Draw();
        it1++;
    }
    auto it2=IMAGENES.begin();
    while(it2!=IMAGENES.end()){
        it2->Draw();
        it2++;
    }
    auto it3=BOTONES.begin();
    while(it3!=BOTONES.end()){
        it3->Draw();
        it3++;
    }
}

Cuadrado2D* Motor2D::addRect(float x, float y,float w, float h){
    RECTANGULOS.emplace_back(x,y,w,h);
    return &RECTANGULOS.back();
}

int Motor2D::checkbuton(){
    if(motor->isLClickPressed()==false){
        return -1;
    }
    double x,y;

    motor->getCursorPosition(x,y);
    for(uint16_t i = 0; i < BOTONES.size(); ++i)
        if(BOTONES[i].checkOn(x, y)){
            return BOTONES[i].getType();
        }

    return -1;
}

void Motor2D::aplyhover(){
    double x,y;
    motor->getCursorPosition(x,y);

    auto it=BOTONES.begin();
    while(it!=BOTONES.end()){

        if(it->checkOn(x, y)){
            ////std::cout << "encima" << '\n';
            //setImage
            if(!it->HasPlayedSound()){
                s_hover->play();
            }

            it->setHover();
        }
        else{
            it->reset();
        }
        it++;
    }
}

// Imagen2D* Motor2D::AddImage(std::string source,float _posx,float _posy,float _width,float _height){
//     float x,y,w,h;
//     x=_posx/100.0;
//     y=_posy/100.0;
//     w=(_posx+_width)/100.0;
//     h=(_posy+_height)/100.0;
//     auto nuevo = new Imagen2D(x,y,w,h,source);
//
//
//     IMAGENES.push_back(nuevo);
//     return nuevo;
// }
//
// Boton2D* Motor2D::addButton(float x, float y, float w,float h,EnumButtonType id,std::string imagenP,std::string imagenS,std::string texto,bool focus,glm::vec4 _color){
//     h=(y+h)/100.0;
//     w=(x+w)/100.0;
//     x=x/100.0;
//     y=y/100.0;
//     auto nuevo=new Boton2D(x,y,w,h,id,imagenP,imagenS,texto,focus);
//     nuevo->setColor(_color);
//     // BOTONES.push_back(nuevo);
//     return nuevo;
// }

void Motor2D::addText(float x, float y,const std::string &Name,glm::vec4 _color,float tam){
    x=x/100.0;
    y=y/100.0;
    auto nuevo=new Texto2D( x, y,Name,_color,tam);
    // TEXT.push_back(nuevo);//
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
    // //std::cout << "hacemos algo" << '\n';
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
    // //std::cout << "id:" <<id<< '\n';
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


    //addButton(45,50,10,9,CONTINUE,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","Continuar",true);
    return 1;

}

//Menu principal
int Motor2D::InitPause(){
    CLINMenu();

    AssetManager* AM = Singleton<AssetManager>::Instance();
    IMAGENES.emplace_back(35/1280.f, 100/720.f, 254/1280.f, 196/720.f, AM->getTexture("assets/HUD/PAUSA.png") );

    BOTONES.emplace_back(84/1280.f, 236/720.f, 251/1280.f, 285/720.f, CONTINUE,    AM->getConstantTexture("assets/HUD/CONTINUAR.png"),      AM->getConstantTexture("assets/HUD/CONTINUAR_HOVER.png") );
    BOTONES.emplace_back(84/1280.f, 301/720.f, 226/1280.f, 350/720.f, GOOPTIONS,   AM->getConstantTexture("assets/HUD/OPCIONES_Pause.png"), AM->getConstantTexture("assets/HUD/OPCIONES_Pause_HOVER.png"));
    BOTONES.emplace_back(84/1280.f, 366/720.f, 307/1280.f, 415/720.f, RETURNMENU,  AM->getConstantTexture("assets/HUD/SALIR_AL_MENU.png"),  AM->getConstantTexture("assets/HUD/SALIR_AL_MENU_HOVER.png"));
    BOTONES.emplace_back(84/1280.f, 435/720.f, 391/1280.f, 484/720.f, CLOSE,       AM->getConstantTexture("assets/HUD/SALIR_DELTO.png"),    AM->getConstantTexture("assets/HUD/SALIR_DELTO_HOVER.png"));

    return 3;

}
//Main Menu
int Motor2D::InitMenu(){
    CLINMenu();
    //AddImage("assets/HUD/menu.png",0,0,100,100);
    //addText(45,10,"Menu principal");

    // auto but1=addButton(39,57,9,12,GOPLAY,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","Play");
    AssetManager* AM = Singleton<AssetManager>::Instance();
    BOTONES.emplace_back(561/1280.f, 460/720.f, 723/1280.f, 569/720.f,START, AM->getTexture("assets/HUD/PLAY.png"), AM->getTexture("assets/HUD/PLAY_HOVER.png") );
    BOTONES.emplace_back(142/1280.f, 601/720.f, 364/1280.f, 692/720.f,GOOPTIONS, AM->getTexture("assets/HUD/OPTIONS.png"), AM->getTexture("assets/HUD/OPTIONS_HOVER.png"));
    BOTONES.emplace_back(552/1280.f, 601/720.f, 774/1280.f, 692/720.f,GOCREDITS, AM->getTexture("assets/HUD/CREDITS.png"), AM->getTexture("assets/HUD/CREDITS_HOVER.png"));
    BOTONES.emplace_back(964/1280.f, 601/720.f, 1141/1280.f, 692/720.f,CLOSE, AM->getTexture("assets/HUD/EXIT.png"), AM->getTexture("assets/HUD/EXIT_HOVER.png"));

    IMAGENES.emplace_back(200/1280.f, 72/720.f, 1091/1280.f, 286/720.f, Singleton<AssetManager>::Instance()->getTexture("assets/HUD/THEHIVE.png"));
    return 4;
}

//Jugar
int Motor2D::InitMenu2(){
    CLINMenu();
    // AddImage("assets/HUD/menucerca.png",0,0,100,100);
    //
    // //addText(45,10,"Play");
    // addButton(40,21,20,10,DIFF1,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","Larva",true);
    // addButton(40,33,20,10,DIFF2,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","Alien");
    // addButton(40,45,20,10,DIFF3,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","The hive");
    // addButton(30,60,40,20,START,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","Play");
    //
    // addButton(20,20,5,9,GOMAIN,"assets/HUD/Botonsoloatras.png","assets/HUD/Botonsoloatras.png","");
return 5;
}
//Creditos
int Motor2D::InitMenu3(){
    CLINMenu();
    // AddImage("assets/HUD/menucerca.png",0,0,100,100);
    //
    // //addText(45,10,"Credits");
    // addButton(20,20,5,9,GOMAIN,"assets/HUD/Botonsoloatras.png","assets/HUD/Botonsoloatras.png","");

    return 1;
}

//Opciones
int Motor2D::InitOptions(){
    CLINMenu();
    RECTANGULOS.emplace_back(0, 0, 1, 1);
    RECTANGULOS.back().setTransparency(0.95);
    RECTANGULOS.back().setColor(glm::vec3(0,0,0));
    RECTANGULOS.back().setZindex(-0.995);

    AssetManager* AM = Singleton<AssetManager>::Instance();
    BOTONES.emplace_back(82/1280.f, 73/720.f, 154/1280.f, 149/720.f,CONTINUE, AM->getTexture("assets/HUD/Botonsoloatras.png"), AM->getTexture("assets/HUD/BACK_HOVER.png") );

    // AddImage("assets/HUD/menucerca.png",0,0,100,100);
    //
    // //addText(45,10,"Options");
    // addButton(40,31,20,10,GOVIDEO,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","Graphics");
    // addButton(40,43,20,10,GOMUSIC,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","Audio");
    // addButton(40,55,20,10,GOCONTROLLS,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","Controlls");
    //
    // addButton(20,20,5,9,CONTINUE,"assets/HUD/Botonsoloatras.png","assets/HUD/Botonsoloatras.png","");
    return 4;
}

//graficos
int Motor2D::InitMenu5(){
    CLINMenu();
    // AddImage("assets/HUD/menucerca.png",0,0,100,100);
    //
    // //addText(45,10,"Video");
    // addButton(20,20,5,9,GOINITOPTIONS,"assets/HUD/Botonsoloatras.png","assets/HUD/Botonsoloatras.png","");

    return 1;
}
//sonido
int Motor2D::InitMenu6(){
    CLINMenu();

    //AddImage("assets/HUD/menucerca.png",0,0,100,100);




    //addText(45,10,"Audio"    );
    // addText(35,41,"Dialogues"    );
    // addText(45,41, std::to_string(VolDialogo));
    // addButton(55,40,2,5,MOREDIALOD,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","+");
    // addButton(58,40,2,5,LESSDIALOD,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","-");
    // addButton(61,40,2,5,MUTEDIALOD,"assets/HUD/mute.png","assets/HUD/mute.png","");
    if(muteDialog){
        muteDialog = false;
        colorMute(MUTEDIALOD);
    };


    addText(35,47,"Music"  );
    addText(45,47,std::to_string(VolMusic));
    // addButton(55,46,2,5,MOREMUSIC,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","+");
    // addButton(58,46,2,5,LESSMUSIC,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","-");
    // addButton(61,46,2,5,MUTEMUSIC,"assets/HUD/mute.png","assets/HUD/mute.png","");
    if(muteMusic){
        muteMusic = false;
        colorMute(MUTEMUSIC);
    };

    addText(35,53,"Effects"    );
    addText(45,53, std::to_string(VolEffect) );
    // addButton(55,52,2,5,MOREEFFECT,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","+");
    // addButton(58,52,2,5,LESSEFFECT,"assets/HUD/Botonsolo.png","assets/HUD/Botonsolo.png","-");
    // addButton(61,52,2,5,MUTEEFFECT,"assets/HUD/mute.png","assets/HUD/mute.png","");
    if(muteEffect){
        muteEffect = false;
        colorMute(MUTEEFFECT);
    };

    //addButton(20,20,5,9,GOINITOPTIONS,"assets/HUD/Botonsoloatras.png","assets/HUD/Botonsoloatras.png","");

    return 7;
}
//controles
int Motor2D::InitMenu7(){
    CLINMenu();
    //AddImage("assets/HUD/menucerca.png",0,0,100,100);

    //addText(45,10,"Controlls");

    //addButton(20,20,5,9,GOINITOPTIONS,"assets/HUD/Botonsoloatras.png","assets/HUD/Botonsoloatras.png","");

    return 1;
}
//int Motor2D::InitTuto(){
//    CLINMenu();
//    //AddImage("assets/HUD/menucerca.png",0,0,100,100);
//    addText(30,63,"Effects"    );
//
//    return 1;
//}


void Motor2D::InitHUD(){
    CLINMenu();

    // AddImage("assets/HUD/hab1.png",  2, 90,7,10);
    // auto boton=addRect(                     2, 90,7,10);
    // boton->setColor(glm::vec4(1,1,1,0.25));
    //
    //
    // AddImage("assets/HUD/hab2.png",  12, 90,7,10);
    // boton=addRect(                          12, 90,7,10);
    // boton->setColor(glm::vec4(1,1,1,0.25));
    //
    //
    // AddImage("assets/HUD/hab3.png",  22,90,7,10);
    // //AddImage("hab3","assets/HUD/AMETRALLADORA_HUD.png",  22,90,7,10);
    // boton=addRect(                          22,90,7,10);
    // boton->setColor(glm::vec4(1,1,1,0.25));

    //
    // float _x,_y,x,y,w,h;
    // x=75;
    // y=85;
    // w=20;
    // h=15;
    // _x= x+w*0.65;
    // _y= y+h*0.7;
    // auto yep=AddImage(imgarmaS,75,85,20,15);//secundaria
    // yep->setShader("2D_im");
    // yep->setZindex(-0.9997);
    // addText(_x, _y,"arma0",glm::vec4(1,1,1,1),30);
    // x=70;
    // y=80;
    // w=20;
    // h=15;
    // _x= x+w*0.65;
    // _y= y+h*0.7;
    // //AddImage("1arma","assets/HUD/AMETRALLADORA_HUD.png",70,80,20,15); // Principal
    // yep=AddImage(imgarmaP,70,80,20,15); // Principal
    // yep->setShader("2D_im");
    // yep->setZindex(-0.9998);
    // addText(_x, _y,"arma1",glm::vec4(1,1,1,1),30);
    //
    //
    // AddImage("assets/HUD/Vida.png",  60,3.77,35,7);
    // boton=addRect(                          60,2,35,7);
    // boton->setColor(glm::vec4(0,0.5,0,1));
    // boton->setZindex(-0.9998);
    // boton=addRect(                          0.665,0.0377,0.95,0.1047);
    // boton->setColor(glm::vec4(0.4,0.4,0.4,1));
    // boton->setZindex(-0.9997);
    // //cruceta
    // float anchura,longitud,c;
    //
    // //cruceta negra
    // anchura=0.002;
    // longitud=0.011;
    // c=0.5;
    // boton=addRect(c-longitud,c-anchura,c+longitud,c+anchura);
    // boton->setColor(glm::vec4(0,0,0,1));
    // //ratio d epantalla para tenerlo exacto :D
    // anchura=0.0012;
    // longitud=0.0185;
    // boton=addRect(c-anchura,c-longitud,c+anchura,c+longitud);
    // boton->setColor(glm::vec4(0,0,0,1));
    //
    // //cruceta blanca
    //
    // anchura=0.001;
    // longitud=0.01;
    // c=0.5;
    // boton=addRect(c-longitud,c-anchura,c+longitud,c+anchura);
    // boton->setColor(glm::vec4(100,100,100,1));
    // //ratio d epantalla para tenerlo exacto :D
    // anchura=0.001;
    // longitud=0.0165;
    // boton=addRect(c-anchura,c-longitud,c+anchura,c+longitud);
    // boton->setColor(glm::vec4(100,100,100,1));



    //AddImage("G1","assets/HUD/Botonsolo.png",porc_ancho(2),porc_alto(2),porc_alto(10),porc_alto(10));
    //AddImage("G2","assets/HUD/Botonsolo.png",porc_ancho(13),porc_alto(2),porc_alto(10),porc_alto(10));
    //AddImage("G3","assets/HUD/Botonsolo.png",porc_ancho(24),porc_alto(2),porc_alto(10),porc_alto(10));

    // MAPA A FUNCIONES MOLON
    //mapHudFunctions[0]=&Motor2D::HUD_hability1;
    //mapHudFunctions[1]=&Motor2D::HUD_hability2;
    //mapHudFunctions[2]=&Motor2D::HUD_hability3;
    //mapHudFunctions[3]=&Motor2D::HUD_vida;
    //mapHudFunctions[4]=&Motor2D::HUD_arma0;
    //mapHudFunctions[5]=&Motor2D::HUD_arma1;
//pintarTexto();
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
void Motor2D::clinpopup(){
    if(pop){
        delete POUP;
        pop=false;
    }
}

void Motor2D::pintarTexto(int nlineas,std::string texto[]){

    //no se usa con el texto
    /*//fondo
    auto boton=addRect(0.2,0.2,0.8,0.8);
    //texto
    // valores porcentuales (0--100)
    int tam=30;
    //int nlineas=4;
    int x_parrafo=25;
    int y_parrafo=25;
    int interliniado=5;
    glm::vec4 color =glm::vec4(1,0,0,1);
    //std::string texto[]{
    //    "German es muy muy gay",
    //    "Effects",
    //    "Effects",
    //    "Effects"
    //};
    //incluimos cada liena
    for (size_t i = 0; i < nlineas; i++) {
        addText(x_parrafo,y_parrafo+interliniado*i,texto[i],color,tam);
    }
    */

}
void Motor2D::CLINTexto(){
    // auto it=TEXT.begin();
    // it++;
    // if(TEXT.size()>2){
    //     for (size_t i = 2; i < TEXT.size(); i++) {
    //         //TEXT[i]->Draw();
    //         //delete (TEXT[i]);
    //         TEXT.erase(it);
    //         it++;
    //
    //     }
    // }
    //RECTANGULOS[7]->Draw();

    auto it2=RECTANGULOS.begin();
    for (size_t e = 0; e < 8; e++) {
        /* code */
        it2++;
    }
    //delete (RECTANGULOS[7]);
    RECTANGULOS.erase(it2);


}
void Motor2D::CLINMenu(){

    BOTONES.clear();
    IMAGENES.clear();
    RECTANGULOS.clear();

}

void Motor2D::CLINNormal(){
    //liberar eso
    //std::vector<Cuadrado2D*> RECTANGULOS;
    //std::vector<Boton2D*> BOTONES;
    //std::vector<Boton2D*> TEXT;
    IMAGENES.clear();

    // auto it2=TEXT.begin();
    // while(it2!=TEXT.end()){
    //     delete (*it);
    //     it2++;
    // }
    // TEXT.clear();
}
