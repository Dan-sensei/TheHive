#ifndef _CREDITSTATE_H
#define _CREDITSTATE_H

#include <Omicron/Omicron.hpp>
#include <Omicron/2D/Motor2D.hpp>
class CTriggerSystem;

class ObjectManager;
class ggDynWorld;

//#include <iostream>
#include <vector>
#include "States/State.hpp"
#include <Omicron/2D/GUIController.hpp>
#include <FMOD/SoundSystem.hpp>

class CreditState : public State{
public:
    CreditState();
    CreditState(const CreditState &orig) = delete;
    ~CreditState();
    //void update();
    //void RUN();
    virtual void CLIN();
    virtual void Init();
    virtual void Update();
    void updateText();
    virtual void Resume();
    virtual void Pause() { }

    /*

    virtual void HandleInput() = 0;
    virtual void Draw(float dt) = 0;

    virtual void Pause() { }
    virtual void Resume() { }

    */

private:


    int tam;
    int x_parrafo;
    int y_parrafo;
    double interliniado;
    glm::vec4 color;

    std::vector<std::string> texto;
    std::vector<Texto2D*> textoCreado;
    int it;

    void nextstep();

    Omicron* Engine;
    Motor2D* Engine2D;
    CTriggerSystem* EventSystem;
    ObjectManager* Manager;
    ggDynWorld* world;
    GUIController* cont;

    SoundSystem* SS;

    gg::Clock MasterClock;
    double DeltaTime;
    float Accumulator;

};


#endif
