
#include "EventRec.hpp"
#include <iostream>

//class GameEngine;

EventRec::EventRec(SAppContext & context) : Context(context)
{ }
bool EventRec::OnEvent(const irr::SEvent& event){
    std::cout << "evento" << '\n';
    if (event.EventType == irr::EET_GUI_EVENT)
    {
        irr::s32 id = event.GUIEvent.Caller->getID();
        irr::gui::IGUIEnvironment* env = Context.device->getGUIEnvironment();
        switch(event.GUIEvent.EventType)
        {
            case irr::gui::EGET_SCROLL_BAR_CHANGED:
                if (id == GUI_ID_TRANSPARENCY_SCROLL_BAR)
                {
                    irr::s32 pos = ((irr::gui::IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
                    //setSkinTransparency(pos, env->getSkin());do things
                }
                break;
            case irr::gui::EGET_BUTTON_CLICKED:
                switch(id){
                case 0:
                std::cout << "0" << '\n';
                    //Context.device->closeDevice();
                    return true;
                }
                break;
                case 1:
                std::cout << "1" << '\n';
                //Context.listbox->addItem("hola");

                    //Context.device->closeDevice();
                    return true;
                break;
                case 2:
                std::cout << "2" << '\n';
                    //Context.device->closeDevice();
                    return true;
                break;
        }
    }
    return false;
}
/*
EventRec::EventRec(SAppContext & context) : Context(context)
{ }
bool EventRec::OnEvent(const SEvent& event){

}
*/
