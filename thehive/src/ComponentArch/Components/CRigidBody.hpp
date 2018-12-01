#ifndef _CRIGIDBODY_H
#define _CRIGIDBODY_H

#include <vector>

#include <Singleton.hpp>
#include <ComponentArch/IComponent.hpp>         // [OBLIGATORIO]
#include <ComponentArch/Message.hpp>            // [OPCIONAL] Si necesitas recibir mensajes o inicializar variables punteros a otras componentes
#include <GameEngine/GameEngine.hpp>            // [OPCIONAL] Si necesitas acceder a algún método de GameEngine
#include <ComponentArch/ObjectManager.hpp>      // [OPCIONAL] Si necesitas acceder a algún método de ObjectManager

#include "EventSystem/CTriggerSystem.hpp"

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <BulletWorldImporter/btBulletWorldImporter.h>
#include <Bullet/ggDynWorld.hpp>

#include <EventSystem/Blackboard.hpp>
#include <EventSystem/BRbData.hpp>
#include <EventSystem/BFloat.hpp>

class ggDynWorld;

//  Forward declaration de otras componentes que incluyas
class CTransform;
class CClock;

class CRigidBody : public IComponent {
    public:
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
        CRigidBody(const CRigidBody &orig) = delete;
        virtual ~CRigidBody();

        // Functions of IComponent
        static void initComponent();
        virtual gg::EMessageStatus processMessage(const Message &m);    // [OPCIONAL] (Obligatorio si referencias a otras componentes)
        virtual void Init();         // [OBLIGATORIO] Aunque esté vacío en el .cpp

        // Handlers                                 // Funciones que se llaman dependiendo del mensaje que recibas
        gg::EMessageStatus MHandler_SETPTRS ();     // IMPORTANTE: SETPTRS Se usará para inicializar punteros a otras componentes
        gg::EMessageStatus MHandler_UPDATE  ();
        gg::EMessageStatus MHandler_DOACTION(Message);
        void MHandler_XPLOTATO(TriggerRecordStruct* cdata);

        // Funciones de CRigidBody
        void applyCentralForce(gg::Vector3f);
        void applyCentralImpulse(gg::Vector3f);
        void applyTorque(gg::Vector3f);

        void setLinearVelocity(gg::Vector3f);

        gg::Vector3f getVelocity();
        gg::Vector2f getXZVelocity();

        // 'Despierta' de nuevo el objeto para que les puedan ser aplicadas fuerzas
        void activate(bool);

        gg::Vector3f getBodyPosition();
        gg::Vector3f getLinearVelocity();

        // Funciones del mapa
        void updateCTransformPosition();
        void Upd_MoverObjeto();
    private:
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

        // Update personalizado, Amstrad wannabe
        using pFunc = void (CRigidBody::*)();
        std::map<EnumActionType, pFunc> mapaFuncUpdate;
        pFunc actualUpd;
};

#endif
