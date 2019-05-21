#include "PopState.hpp"

#include <iostream>
#include <cstdint>
#include <string>
#include <stack>
#include "Singleton.hpp"

#include <Omicron/2D/Motor2D.hpp>

#include "Factory.hpp"
#include <States/StateMachine.hpp>



#define MOVEMENT_SPEED 1.f



PopState::PopState()
{
    Engine = Singleton<Omicron>::Instance();
    SS = Singleton<SoundSystem>::Instance();
    SH = Singleton<AssetManager>::Instance()->getShader("Image");
}

PopState::~PopState(){
    glDeleteVertexArrays(1, &QUAD);
    glDeleteBuffers(1, &QUAD_POS_UV);

    CLIN();
}
void PopState::Addim(unsigned int im){
    imagenes.push_back(im);
}

void PopState::Init(){
    Engine->HideCursor(false);
    //Singleton<Motor2D>::Instance()->InitPause();
    //Singleton<Motor2D>::Instance()->InitPause();

    float RENDER_QUAD[] = {
        -1.0f,  1.0f, 0.0f, -1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f,  1.0f, 1.0f, -1.0f,
         1.0f, -1.0f, 1.0f, 0.0f,
    };

    glGenVertexArrays(1, &QUAD);

        glGenBuffers(1, &QUAD_POS_UV);
        glBindVertexArray(QUAD);
        glBindBuffer(GL_ARRAY_BUFFER, QUAD_POS_UV);
        glBufferData(GL_ARRAY_BUFFER, sizeof(RENDER_QUAD), &RENDER_QUAD, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glVertexAttribFormat(0, 2, GL_FLOAT, false, 0);
        glVertexAttribFormat(1, 2, GL_FLOAT, false, 8);

        glVertexAttribBinding(0, 0);
        glVertexAttribBinding(1, 0);

        glBindVertexBuffer(0, QUAD_POS_UV, 0, 16);

    glBindVertexArray(0);

    //_GUIController->musicaMenuPlay();
    //Engine->createCamera(glm::vec3(0, /* message */30, 30), glm::vec3(0, 0, 0));
}

void PopState::siguiente(){
    if(imagenes.size()){
        Singleton<AssetManager>::Instance()->freeTexture(imagenes.front());
        imagenes.erase(imagenes.begin());
    }

    if(imagenes.empty()){
        Singleton<StateMachine>::Instance()->RemoveStates();
    }
}

void PopState::Resume(){
    Init();
}

//void PopState::submenu(){
//    CLIN();
//}

void PopState::Update(){


    Engine->PollEvents();
    if(Engine->key(gg::X, true))  {
        siguiente();
    }

    if(imagenes.empty()) return;

    Engine->BeginDraw();
    Engine->draw();

    SH->Bind();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, imagenes.front());

    glBindVertexArray(QUAD);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    Engine->EndDraw();
    //Engine->resetClickVariable();

    SS->update();

}

void PopState::CLIN(){

    Singleton<Motor2D>::Instance()->clinpopup();
    Singleton<Motor2D>::Instance()->CLINMenu();
    //_GUIController->musicaMenuStop();
}
