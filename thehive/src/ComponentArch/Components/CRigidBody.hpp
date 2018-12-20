#ifndef _CRIGIDBODY_H
#define _CRIGIDBODY_H

#include <vector>

#include <Singleton.hpp>
#include <ComponentArch/IComponent.hpp>         // [OBLIGATORIO]
#include <ComponentArch/Message.hpp>            // [OPCIONAL] Si necesitas recibir mensajes o inicializar variables punteros a otras componentes
#include <GameEngine/GameEngine.hpp>            // [OPCIONAL] Si necesitas acceder a algún método de GameEngine
#include <ComponentArch/ObjectManager.hpp>      // [OPCIONAL] Si necesitas acceder a algún método de ObjectManager

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <BulletWorldImporter/btBulletWorldImporter.h>
#include <Bullet/ggDynWorld.hpp>

//  Forward declaration de otras componentes que incluyas
class CTransform;

class CRigidBody : public IComponent {
    public:
        // Constructor normal
        CRigidBody(
            bool kinematic,
            bool loadedFromPath,
            std::string path,
            float x, float y, float z,
            float sX, float sY, float sZ,
            float _mass,
            float iX, float iY, float iZ,
            float friction = 0
        );
        // Constructor de objetos fantasma -> DETECTAN TODAS LAS COLISIONES, PERO NO COLISIONAN
        CRigidBody(
            bool,
            float,float,float,
            float,float,float
        );
        CRigidBody(const CRigidBody &orig) = delete;
        virtual ~CRigidBody();

        // Functions of IComponent
        virtual gg::EMessageStatus processMessage(const Message &m);    // [OPCIONAL] (Obligatorio si referencias a otras componentes)
        virtual void Init();
        virtual void FixedUpdate();

        // Handlers                                 // Funciones que se llaman dependiendo del mensaje que recibas
        gg::EMessageStatus MHandler_SETPTRS ();     // IMPORTANTE: SETPTRS Se usará para inicializar punteros a otras componentes

        gg::EMessageStatus SavePreviousStatus ();
        gg::EMessageStatus SaveCurrentStatus ();
        gg::EMessageStatus Interpolate (const Message &_Tick);

        gg::EMessageStatus MHandler_DOACTION(Message);
        // Funciones de CRigidBody
        void applyCentralForce(gg::Vector3f);
        void applyCentralImpulse(gg::Vector3f);
        void applyTorque(gg::Vector3f);
        void applyConstantVelocity(gg::Vector3f,float,bool = true);

        void setLinearVelocity(gg::Vector3f);

        gg::Vector3f getVelocity();
        gg::Vector2f getXZVelocity();

        // 'Despierta' de nuevo el objeto para que les puedan ser aplicadas fuerzas
        void activate(bool);

        gg::Vector3f getBodyPosition();
        gg::Vector3f getLinearVelocity();
        void setBodyPosition(gg::Vector3f&);
        void setOffsetBodyPosition(gg::Vector3f&);

        bool checkContactResponse();

        // Funciones del mapa
        void updateCTransformPosition();
        void Upd_MoverObjeto();

        void moveUp();
        void moveDown();
    private:
        struct Status {
            Status();
            Status(const Status &orig);
            ~Status();

            gg::Vector3f Position;
            gg::Vector3f Rotation;
        };

        Status Previous;
        Status Current;

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
