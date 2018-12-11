#ifndef EVENTREC_H
#define EVENTREC_H

#include <irrlicht/irrlicht.h>
//#include <string>
//#include "Singleton.hpp"
//#include "Util.hpp"
//#include <list>
//#include <map>

//class GameEngine;
struct SAppContext
{
    irr::IrrlichtDevice *device;
    irr::s32             counter;
    //irr::gui::IGUIListBox*    listbox;
};
class EventRec{
    //friend class Singleton<ScreenConsole>;
    //friend class GameEngine;
    public:
         EventRec(SAppContext& context);
         virtual bool OnEvent(const irr::SEvent& event);
    private:
        SAppContext & Context;
};
enum
{
    GUI_ID_QUIT_BUTTON = 101,
    GUI_ID_NEW_WINDOW_BUTTON,
    GUI_ID_FILE_OPEN_BUTTON,
    GUI_ID_TRANSPARENCY_SCROLL_BAR
};


#endif
