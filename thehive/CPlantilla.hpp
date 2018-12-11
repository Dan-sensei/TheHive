#ifndef _CPlantilla_H
#define _CPlantilla_H

#include <ComponentArch/IComponent.hpp>         // [OBLIGATORIO]
#include <ComponentArch/Message.hpp>            // [OPCIONAL] Si necesitas recibir mensajes o inicializar variables
                                                //            punteros a otras componentes


class GameEngine;        //  [OPCIONAL] Si necesitas acceder a algún método de GameEngine
class ObjectManager;     //  [OPCIONAL] Si necesitas acceder a algún método de ObjectManager

class CCamera;           //  Forward declaration de otras componentes que incluyas
class CTransform;

class CPlantilla : public IComponent {
    friend class ObjectManager;                 // Con esto le decimos que sólo ObjectManager puede crear esta componente
    public:
        CPlantilla(Var 1, Var 2);                    //  <<-- AHORA PUEDE RECIBIR PARÁMETROS!
        CPlantilla(const CPlantilla &orig) = delete;
        virtual ~CPlantilla();

        // Functions of IComponent
        virtual gg::EMessageStatus processMessage(const Message &m);    // [OPCIONAL] (Obligatorio si referencias a otras componentes)
        virtual void Init();                                            // [OPCIONAL]
        virtual void Update();                                          // [OPCIONAL]   Se llama cada 1/60 segundos
        virtual void FixedUpdate();                                     // [OPCIONAL]   Se llama cada 1/15 segundos. Para cáculos.

        // Handlers                                 // Funciones que se llaman dependiendo del mensaje que recibas
        gg::EMessageStatus MHandler_SETPTRS ();     // IMPORTANTE: SETPTRS Se usará para inicializar punteros a otras componentes

    private:


        CCamera *camera;
        GameEngine* engine;

        CTransform* cTransform;     //  Punteros a otras componentes
};

#endif
