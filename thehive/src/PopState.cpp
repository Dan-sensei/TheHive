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
:FADE(Singleton<Fade>::Instance()), UPD(&PopState::NormalUpdate)
{
    Engine = Singleton<Omicron>::Instance();
    SS = Singleton<SoundSystem>::Instance();
    SH = Singleton<AssetManager>::Instance()->getShader("Image");
    imagenes.reserve(3);
}

PopState::~PopState(){
    glDeleteVertexArrays(1, &QUAD);
    glDeleteBuffers(1, &QUAD_POS_UV);

    CLIN();
}
void PopState::Addim(unsigned int TextureID){
    imagenes.push_back(TextureID);
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

    nextImage = new SonidoNormal();
    SS->createSound("event:/SFX/Menu/Aceptar", nextImage);
    //_GUIController->musicaMenuPlay();
    //Engine->createCamera(glm::vec3(0, /* message */30, 30), glm::vec3(0, 0, 0));
}

void PopState::setFadeIn(){
    UPD = &PopState::FadeInUpdate;
    FADE->setFadeIn(2.5);
}

void PopState::siguiente(){
    if(imagenes.size()){
        nextImage->play();
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
    Engine->BeginDraw();

    (this->*UPD)();

    Engine->EndDraw();
}

void PopState::FadeInUpdate(){
    NormalUpdate();
    if(FADE->Draw()){
        UPD = &PopState::NormalUpdate;
    }
}

void PopState::NormalUpdate(){

    Engine->PollEvents();
    if(Engine->key(gg::X, true))  {
        siguiente();
    }

    if(imagenes.empty()) return;

    Engine->draw();

    SH->Bind();

    glUniform1f(3, -0.995f);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, imagenes.front());

    glBindVertexArray(QUAD);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    //Engine->resetClickVariable();

    SS->update();

}

void PopState::CLIN(){
    Singleton<Motor2D>::Instance()->CLINMenu();
    delete nextImage;
    //_GUIController->musicaMenuStop();
}
