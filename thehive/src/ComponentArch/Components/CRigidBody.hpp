#ifndef _CRIGIDBODY_H
#define _CRIGIDBODY_H

#include <vector>

#include <Singleton.hpp>
#include <ComponentArch/IComponent.hpp>         // [OBLIGATORIO]
#include <ComponentArch/Message.hpp>            // [OPCIONAL] Si necesitas recibir mensajes o inicializar variables punteros a otras componentes
#include <GameEngine/GameEngine.hpp>            // [OPCIONAL] Si necesitas acceder a algún método de GameEngine
#include <ComponentArch/ObjectManager.hpp>      // [OPCIONAL] Si necesitas acceder a algún método de ObjectManager
#include <ComponentArch/InitStructs.hpp>

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <BulletWorldImporter/btBulletWorldImporter.h>

#include <Bullet/ggDynWorld.hpp>

class GameEngine;        //  [OPCIONAL] Si necesitas acceder a algún método de GameEngine
class ObjectManager;     //  [OPCIONAL] Si necesitas acceder a algún método de ObjectManager
class ggDynWorld;

//  Forward declaration de otras componentes que incluyas
class CTransform;

class CRigidBody : public IComponent {
    friend class ObjectManager;                 // Con esto le decimos que sólo ObjectManager puede crear esta componente
    public:
        virtual ~CRigidBody();

        // Functions of IComponent
        static void initComponent();
        virtual gg::EMessageStatus processMessage(const Message &m);    // [OPCIONAL] (Obligatorio si referencias a otras componentes)
        virtual void initializeComponentData(const void* data);         // [OBLIGATORIO] Aunque esté vacío en el .cpp

        // Handlers                                 // Funciones que se llaman dependiendo del mensaje que recibas
        gg::EMessageStatus MHandler_SETPTRS ();     // IMPORTANTE: SETPTRS Se usará para inicializar punteros a otras componentes
        gg::EMessageStatus MHandler_UPDATE  ();
        gg::EMessageStatus MHandler_XPLOTATO(const Message &m);

        // Funciones de CRigidBody
        void applyCentralForce(gg::Vector3f);
        void applyCentralImpulse(gg::Vector3f);
        void applyTorque(gg::Vector3f);

        void setLinearVelocity(gg::Vector3f);

        // 'Despierta' de nuevo el objeto para que les puedan ser aplicadas fuerzas
        void activate(bool);

        gg::Vector3f getBodyPosition();

    private:
        CRigidBody();                //  No queremos que alguien lo construya fuera (Limón)
        CRigidBody(const CRigidBody &orig) = delete;

        GameEngine* engine;
        ggDynWorld* world;


        //  Punteros a otras componentes
        CTransform* cTransform;

        //  Variables de esta componente
        btDefaultMotionState*       myMotionState;
        btCollisionShape*           shape;
        btTransform                 transform;
        btRigidBody*                body;

        // Variables de 'ayuda'
        btBulletWorldImporter*      fileLoader;
};

#endif
