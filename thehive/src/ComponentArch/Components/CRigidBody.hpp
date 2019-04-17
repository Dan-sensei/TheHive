#ifndef _CRIGIDBODY_H
#define _CRIGIDBODY_H

#include <vector>

#include <Singleton.hpp>
#include <ComponentArch/IComponent.hpp>         // [OBLIGATORIO]
#include <ComponentArch/Message.hpp>            // [OPCIONAL] Si necesitas recibir mensajes o inicializar variables punteros a otras componentes
            // [OPCIONAL] Si necesitas acceder a algún método de GameEngine
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
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

class ggDynWorld;

//  Forward declaration de otras componentes que incluyas
class CTransform;
class CStaticModel;
class CClock;

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
            //unsigned int Group=0,
            //unsigned int Mask=0
        );
        // Constructor de objetos fantasma -> DETECTAN TODAS LAS COLISIONES, PERO NO COLISIONAN
        CRigidBody(
            bool,
            float,float,float,
            float,float,float
        );

        CRigidBody(
            float x, float y, float z,
            float rx, float ry, float rz, float rw,
            float sX, float sY, float sZ
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
        void MHandler_XPLOTATO(TriggerRecordStruct* cdata);

        // Funciones de CRigidBody
        void clearForce();
        void applyCentralForce(glm::vec3);
        void applyCentralImpulse(glm::vec3);
        void applyTorque(glm::vec3);
        void applyConstantVelocity(glm::vec3,float,bool = true);
        void applyConstantVelocityNormal(glm::vec3,float);

        void setLinearVelocity(glm::vec3);

        // Just virtual, doesn't rotate the actual RigidBody
        void setVirtualRotation(const glm::quat &Quaternion);
        glm::quat getVirtualRotation();

        glm::vec3 getVelocity();
        glm::vec2 getXZVelocity();

        // 'Despierta' de nuevo el objeto para que les puedan ser aplicadas fuerzas
        void activate(bool);

        btRigidBody* getBody();
        glm::vec3 getBodyPosition();
        glm::vec3 getLinearVelocity();
        void setBodyPosition(glm::vec3&);
        void setOffsetBodyPosition(glm::vec3&);

        bool checkContactResponse();

        // Funciones del mapa
        void updateCTransformPosition();
        void Upd_MoverObjeto();
    private:

        struct Status {
            Status();
            Status(const Status &orig);
            ~Status();

            glm::vec3 Position;
            glm::quat Rotation;
        };

        Status Previous;
        Status Current;

        ggDynWorld* world;

        //  Punteros a otras componentes
        CTransform* cTransform;
        CStaticModel* cStaticModel;

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
