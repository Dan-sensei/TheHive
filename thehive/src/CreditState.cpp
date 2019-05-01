#include "CreditState.hpp"

//#include <iostream>
#include <cstdint>
#include <string>
#include <stack>

#include "ComponentArch/ObjectManager.hpp"
#include "Singleton.hpp"

#include <Omicron/2D/Motor2D.hpp>
#include <EventSystem/CTriggerSystem.hpp>
#include <States/StateMachine.hpp>

#include <Omicron/2D/Texto2D.hpp>

#define MOVEMENT_SPEED 1.f


//Funciones de Fran Gallego para imprimir memoria por consola ==============================¬
//                                                                                          |
//====================================================================================      |
// Pretty print a 2-digits hexadecimal value                                                |
//====================================================================================      |
/*
void printHexVal(uint16_t val) {
   // //std::cout << std::hex << std::setw(2) << std::setfill('0') << val;
}

//====================================================================================
// Print a memory slice as raw bytes
//====================================================================================
void printRawMem(uint8_t* p, uint16_t linebytes, uint16_t lines) {
   for(uint16_t l=0; l < lines; ++l) {
      // //std::cout << reinterpret_cast<uint16_t*>(p) << " ";
      for(uint16_t u=0; u < linebytes; ++u) {
         printHexVal(*p);
         ++p;
         // //std::cout << " ";
      }
      // //std::cout << "\n";
   }
}
*/
//============================================================================================

CreditState::CreditState(){
    Engine = Singleton<Omicron>::Instance();
    cont = Singleton<GUIController>::Instance();
    //EventSystem = Singleton<CTriggerSystem>::Instance();
    SS = Singleton<SoundSystem>::Instance();
    Engine2D=Singleton<Motor2D>::Instance();
    Engine->HideCursor(false);
}

CreditState::~CreditState(){
    CLIN();
}

void CreditState::Init(){
    Accumulator = 0;
    MasterClock.Restart();

    //Singleton<Motor2D>::Instance()->InitMenu();
    Engine2D->InitMenu3();

    //int nlineas=4;
    tam=30;
    x_parrafo=35;
    //inicio
    y_parrafo=10;
    //y_parrafo=70;
    //final
    //y_parrafo=82;
    interliniado=0;
    //interliniado=5;


    std::string textoaux[]{
        "German es muy muy gay",
        "Effects",
        "Effects12",
        "Effects3"
    };
    int nlineas=4;
    color =glm::vec4(1,0,0,1);

    //Singleton<Motor2D>::Instance()->pintarCredito(nlineas,texto);
    for (size_t i = 0; i < nlineas; i++) {
        /* code */
        texto.push_back(textoaux[i]);
        //Engine2D->addText(x_parrafo,y_parrafo+interliniado*i,texto[i],color,tam);
    }
    it=0;
    //std::vector<std::string>::iterator it2=texto.begin();

    nextstep();

    Engine->HideCursor(false);

    //cont->musicaMenuPlay();

    //musica_menu->play();

    //Engine->createCamera(glm::vec3(0, 30, 30), glm::vec3(0, 0, 0));
}
void CreditState::Resume() {
    Singleton<Motor2D>::Instance()->InitMenu();
    Engine->HideCursor(false);

    // cont->musicaMenuPause(false);

}
//void CreditState::submenu(){
//    CLIN();

//}

void CreditState::nextstep(){
    auto textoaux=texto.at(it);
    std::cout << " texto = " <<textoaux<< '\n';
    textoCreado.push_back(Engine2D->addText(x_parrafo,y_parrafo+interliniado*0,textoaux,color,tam));
}
void CreditState::updateText(){
    //std::cout << "empezamos" << '\n';
    auto it2=textoCreado.begin();
    while (it2!=textoCreado.end()) {
        if(textoCreado.size()>0){

            Texto2D* text=*it2;
            float y=text->getY();
            y+=0.001;
            text->setY(y);
            //std::cout << "y" <<y<< '\n';
            if(y>=0.82){
            //if(tam==30&&y>=0.82){
                //tam=20;
                //textoCreado.pop_back();
                textoCreado.erase(it2);
                //std::cout << "essage " << '\n';
                Singleton<Motor2D>::Instance()->CLINTexto();
                std::cout << "eliminamos" << '\n';
                if(it2==textoCreado.end()){
                    break;
                }
            }
            it2++;
        }


    }
    std::cout << "int" <<interliniado <<'\n';
    interliniado+=0.001;
    if(interliniado>=0.05){
        std::cout << "entra" << '\n';
        interliniado=0;
        it++;
        if(it<texto.size()){
            std::cout << "entra2" << '\n';//
            nextstep();

        }
        else{
            it=texto.size();
        }
    }
    //std::cout << " message " << '\n';
    //if((*it)->g)

}
void CreditState::Update(){







    DeltaTime = MasterClock.Restart().Seconds();

    Engine->PollEvents();

    if(DeltaTime > 0.25) DeltaTime = 0.25;

    // //std::cout << " - WHILE" << '\n';
    Accumulator += DeltaTime;
    if(Accumulator>0.01){
        updateText();
        Accumulator=0;
    }

    Engine->BeginDraw();
    cont->update();
    //SS->update();
    //Singleton<Motor2D>::Instance()->DisplayMenu();
    //Singleton<StateMachine>::Instance()->AddState(new GameState());
    Singleton<Motor2D>::Instance()->draw();
    Singleton<Motor2D>::Instance()->checkbuton();
    Singleton<Motor2D>::Instance()->aplyhover();
    //Engine2D->draw();
    //Engine2D->checkbuton();

    Engine->EndDraw();
    Engine->resetClickVariable();
}

void CreditState::CLIN(){
    Singleton<Motor2D>::Instance()->CLINMenu();
    //cont->musicaMenuStop();
    //EventSystem->clin();
}
//
// void CreditState::Pause(){
//   cont->musicaMenuPause(true);
// }
