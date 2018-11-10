#ifndef _CKEYBOARD_H
#define _CKEYBOARD_H

#include <ComponentArch/IComponent.hpp>         // [OBLIGATORIO]
#include <ComponentArch/Message.hpp>            // [OPCIONAL] Si necesitas recibir mensajes o inicializar variables
                                                //            punteros a otras componentes


class GameEngine;        //  [OPCIONAL] Si necesitas acceder a algún método de GameEngine
class ObjectManager;     //  [OPCIONAL] Si necesitas acceder a algún método de ObjectManager

class CCamera;           //  Forward declaration de otras componentes que incluyas
class CTransform;

class CKeyboard : public IComponent {
    friend class ObjectManager;                 // Con esto le decimos que sólo ObjectManager puede crear esta componente
    public:
        virtual ~CKeyboard();

        // Functions of IComponent
        static void initComponent();
        virtual gg::EMessageStatus processMessage(const Message &m);    // [OPCIONAL] (Obligatorio si referencias a otras componentes)
        virtual void initializeComponentData(const void* data);         // [OBLIGATORIO] Aunque esté vacío en el .cpp

        // Handlers                                 // Funciones que se llaman dependiendo del mensaje que recibas
        gg::EMessageStatus MHandler_SETPTRS ();     // IMPORTANTE: SETPTRS Se usará para inicializar punteros a otras componentes
        gg::EMessageStatus MHandler_UPDATE  ();

    private:
        CKeyboard();                //  No queremos que alguien lo construya fuera (Limón)
        CKeyboard(const CKeyboard &orig) = delete;


        CCamera *camera;
        GameEngine* engine;

        CTransform* cTransform;     //  Punteros a otras componentes

        gg::Vector2f DASH_SPEED;    //  Variables de esta componente
        gg::Vector2f RUNNING_SPEED;
};

#endif
