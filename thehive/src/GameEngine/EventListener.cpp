#include "EventListener.hpp"
#include <cstdint>
#include <iostream>

EventListener::EventListener(){
    IdButon=-1;
    uint16_t i = irr::KEY_KEY_CODES_COUNT;
    while(i--)  keyMap[i] = false;
}
int EventListener::checkbutton(){
    int aux=IdButon;
    IdButon=-1;
    return aux;
}
bool EventListener::OnEvent(const irr::SEvent& event) {
    // Remember whether each key is down or up
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        keyMap[event.KeyInput.Key] = event.KeyInput.PressedDown;

    if (event.EventType == irr::EET_MOUSE_INPUT_EVENT){
        //  1 ARRIBA
        // -1 ABAJO
        if(event.MouseInput.Event == irr::EMIE_MOUSE_WHEEL){
            wheel = event.MouseInput.Wheel;
            //  1 ARRIBA
            // -1 ABAJO
        //    std::cout << "entra" << '\n';
        //    std::cout << wheel << '\n';
        }
        //else{

        //    //wheel = 0;
        //}

        if (event.MouseInput.Event == irr::EMIE_LMOUSE_PRESSED_DOWN){
            LCLICK = true;
        }
        else if(event.MouseInput.Event == irr::EMIE_LMOUSE_LEFT_UP){
            LCLICK = false;
        }
    }

    if (event.EventType == irr::EET_GUI_EVENT){
        irr::s32 id = event.GUIEvent.Caller->getID();
        if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED){
            IdButon=id;

        }
    }


    return false;
}

// This is used to check whether a key is being held down
bool EventListener::IsKeyDown(gg::KEYCODES key) const {
    return keyMap[key];
}

bool EventListener::isLClickPressed(){
    return LCLICK;
}

int EventListener::getWheelValue(){
    int aux=wheel;
    wheel = 0;
    return aux;
}
