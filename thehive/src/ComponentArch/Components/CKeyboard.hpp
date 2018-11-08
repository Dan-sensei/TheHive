#ifndef _CKEYBOARD_H
#define _CKEYBOARD_H

#include <ComponentArch/IComponent.hpp>
#include <cmath>


class CCamera;
class CTransform;
class GameEngine;

class CKeyboard : public IComponent {
    friend class ObjectManager;
    public:
        virtual ~CKeyboard();

        // Functions of IComponent
        static void initComponent();
        virtual gg::EMessageStatus processMessage();
        virtual void initializeComponentData(const void* data);


    private:
        CKeyboard();
        CKeyboard(const CKeyboard &orig) = delete;

        CTransform* cTransform;
        CCamera *camera;
        GameEngine* engine;
};

#endif
