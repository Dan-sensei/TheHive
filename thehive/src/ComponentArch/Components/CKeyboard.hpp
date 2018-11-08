#ifndef _CKEYBOARD_H
#define _CKEYBOARD_H

#include <cmath>
#include <map>
#include <Singleton.hpp>

#include <GameEngine/KEYCODES.hpp>
#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/ObjectManager.hpp>
#include <GameEngine/GameEngine.hpp>

class CKeyboard : public IComponent {
    friend class ObjectManager;
    public:
        virtual ~CKeyboard();

        // Functions of IComponent
        static void initComponent();
        virtual gg::EMessageStatus processMessage();
        virtual void initializeComponentData(const void* data);
        virtual void initAfterComponentAssigment();



    private:
        CKeyboard();
        CKeyboard(const CKeyboard &orig) = delete;

        // std::map<gg::KEYCODES, gg::Vector3f (*)(void)> moveFunctions;
        gg::Vector2f DASH_SPEED;
        gg::Vector2f RUNNING_SPEED;
};

#endif
