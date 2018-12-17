#include "CRigidBody.hpp"
#include <vector>

#include "CTransform.hpp"
#include "CClock.hpp"

#define PI 3.14159265359
#define FORCE_FACTOR    400.f

std::vector<const char*> names;

CRigidBody::CRigidBody(
    bool kinematic,
    bool loadedFromPath,
    std::string path,
    float x, float y, float z,
    float sX, float sY, float sZ,
    float _mass,
    float iX, float iY, float iZ,
    float friction
)
:cTransform(nullptr), world(nullptr)
{
    // Puntero al mundo de fisicas
    world = Singleton<ggDynWorld>::Instance();

    fileLoader = nullptr;

    if(loadedFromPath){
        fileLoader = new btBulletWorldImporter();
        if(! ( fileLoader->loadFile(path.c_str())) ){
            return;
        }

        btCollisionObject* obj = fileLoader->getRigidBodyByIndex(0);
        body = btRigidBody::upcast(obj);
        shape = body->getCollisionShape();

        // ------------------------

        transform = obj->getWorldTransform();

        transform.setOrigin(btVector3(x,y,z));
        myMotionState = new btDefaultMotionState(transform);
        body->setMotionState(myMotionState);

        // Hago pushback en el vector de 'shapes'
        world->addShape(shape);

        // MASS!=0 ---> RIGIDBODY ES DINAMICO
        // MASS==0 ---> RIGIDBODY ES ESTATICO
        btScalar mass(_mass);
        bool isDynamic = (mass != 0.f);
        btVector3 localInertia;
        if (isDynamic)
        shape->calculateLocalInertia(mass, localInertia);

        // Supongo que es algo que mejora las colisiones y opcional, PERO, sin el myMotionState NO SE PUEDE INICIALIZAR EL BODY =D
        // Using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, localInertia);
        body = new btRigidBody(rbInfo);

        if(friction){
            body->setFriction(btScalar(friction));
        }

        // Add the body to the dynamics world
        world->addRigidBody(body);
    }
    else{
        shape = new btBoxShape(btVector3(btScalar(sX), btScalar(sY), btScalar(sZ)));

        transform.setIdentity();
        transform.setOrigin(btVector3(x,y,z));
        myMotionState = new btDefaultMotionState(transform);

        // Hago pushback en el vector de 'shapes'
        world->addShape(shape);

        // MASS!=0 ---> RIGIDBODY ES DINAMICO
        // MASS==0 ---> RIGIDBODY ES ESTATICO
        btScalar mass(_mass);
        bool isDynamic = (mass != 0.f);
        btVector3 localInertia;
        if (isDynamic)
        shape->calculateLocalInertia(mass, localInertia);

        // Supongo que es algo que mejora las colisiones y opcional, PERO, sin el myMotionState NO SE PUEDE INICIALIZAR EL BODY =D
        // Using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, localInertia);
        body = new btRigidBody(rbInfo);

        // We apply the gravity of the world
        // body->setGravity(btVector3(0,-10,0));
        // body->applyGravity();

        if(friction){
            body->setFriction(btScalar(friction));
        }

        // Add the body to the dynamics world
        world->addRigidBody(body);
    }

    if(kinematic){
        // CF_KINEMATIC_OBJECT = 2
        body->setCollisionFlags(2);
    }

    body->setAngularFactor(btVector3(0,0,0));
}

CRigidBody::CRigidBody(
    bool kinematic,
    float x,float y,float z,
    float sX,float sY,float sZ)
:cTransform(nullptr), world(nullptr)
{
    // Puntero al mundo de fisicas
    world = Singleton<ggDynWorld>::Instance();
    fileLoader = nullptr;

    shape = new btBoxShape(btVector3(btScalar(sX), btScalar(sY), btScalar(sZ)));

    // Hago pushback en el vector de 'shapes'
    world->addShape(shape);

    transform.setIdentity();
    transform.setOrigin(btVector3(x,y,z));
    myMotionState = new btDefaultMotionState(transform);

    // MASS!=0 ---> RIGIDBODY ES DINAMICO
    // MASS==0 ---> RIGIDBODY ES ESTATICO
    btScalar mass(10);
    bool isDynamic = (mass != 0.f);
    btVector3 localInertia;
    if (isDynamic)
    shape->calculateLocalInertia(mass, localInertia);

    // Supongo que es algo que mejora las colisiones y opcional, PERO, sin el myMotionState NO SE PUEDE INICIALIZAR EL BODY =D
    // Using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, localInertia);
    body = new btRigidBody(rbInfo);

    if(kinematic){
        // CF_KINEMATIC_OBJECT = 2
        body->setCollisionFlags(2);
    }

    // CF_NO_CONTACT_RESPONSE
    body->setCollisionFlags( body->getCollisionFlags() | 4);

    // Add the body to the dynamics world
    world->addRigidBody(body);
}

CRigidBody::~CRigidBody() {
    delete myMotionState;
    world->removeRigidBody(body);
    delete body;

    // --------------------
    // Delete de todo lo que he creado con el loadfile

    if(fileLoader){
        fileLoader->deleteAllData();
        delete fileLoader;
    }
    else{
        // Cuando no carga desde fichero
        // Borrar la boxshape que se ha creado
        delete shape;
    }
}

void CRigidBody::Init(){
    world->setGravity(0,-10,0);

    // Hacer set del mapa de punteros a funcion
    mapaFuncUpdate.insert(std::make_pair(Action_AbrirPuerta,&CRigidBody::Upd_MoverObjeto));
    mapaFuncUpdate.insert(std::make_pair(Action_MoverObjeto,&CRigidBody::Upd_MoverObjeto));
    actualUpd = nullptr;

    //  Inicializar punteros a otras compnentes
    MHandler_SETPTRS();
}


gg::EMessageStatus CRigidBody::processMessage(const Message &m) {

    if (m.mType == gg::M_SETPTRS)              return MHandler_SETPTRS     ();
    //else if (m.mType == gg::M_XPLOTATO)     return MHandler_XPLOTATO(m);
    else if (m.mType == gg::M_EVENT_ACTION)         return MHandler_DOACTION    (m);
    else if (m.mType == gg::M_INTERPOLATE_PRESAVE)  return SavePreviousStatus   ();
    else if (m.mType == gg::M_INTERPOLATE_POSTSAVE) return SaveCurrentStatus    ();
    else if (m.mType == gg::M_INTERPOLATE)          return Interpolate    (m);

    return gg::ST_ERROR;
}


//  Message handler functions_______________________________________________________________
//|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |

gg::EMessageStatus CRigidBody::MHandler_DOACTION(Message _mes){
    int *action = static_cast<int*>(_mes.mData);

    // Mapa con funciones de update
    EnumActionType eAction = static_cast<EnumActionType>(*action);
    auto it = mapaFuncUpdate.find(eAction);
    if(it == mapaFuncUpdate.end()){
        return gg::ST_ERROR;
    }
    actualUpd = mapaFuncUpdate[eAction];

    return gg::ST_TRUE;
}

void CRigidBody::MHandler_XPLOTATO(TriggerRecordStruct* cdata){
    if(cTransform){
        float distancia=gg::DIST(cTransform->getPosition(),cdata->vPos);
        float fuerzabomba=cdata->data.find(kDat_Damage);
        gg::Vector3f sol =gg::Normalice(cTransform->getPosition()-cdata->vPos)*fuerzabomba*(1-distancia/cdata->fRadius);

        applyCentralForce(sol);
    }
}

gg::EMessageStatus CRigidBody::MHandler_SETPTRS(){
    // Inicializando punteros
    cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));

    return gg::ST_TRUE;
}

void CRigidBody::Update(){
    // UPDATE

    // COPIA-PEGA DE LA DOCUMENTACION:
    // Bullet automatically deactivates dynamic rigid bodies, when the velocity is below a threshold for a given time.
    // Deactivated (sleeping) rigid bodies don't take any processing time, except a minor broadphase collision detection impact
    // (to allow active objects to activate/wake up sleeping objects)
    body->activate(true);

    if(actualUpd)
        (this->*actualUpd)();
    updateCTransformPosition();
}

void CRigidBody::applyCentralImpulse(gg::Vector3f vec){
    body->applyCentralImpulse(btVector3(vec.X,vec.Y,vec.Z));
}

void CRigidBody::applyCentralForce(gg::Vector3f vec){
    body->applyCentralForce(btVector3(vec.X,vec.Y,vec.Z));
}

void CRigidBody::applyTorque(gg::Vector3f vec){
    body->applyTorque(btVector3(vec.X,vec.Y,vec.Z));
}

void CRigidBody::setLinearVelocity(gg::Vector3f vec){
    body->setLinearVelocity(btVector3(vec.X,vec.Y,vec.Z));
}

void CRigidBody::applyConstantVelocity(gg::Vector3f _force,float _max_speed,bool _keyPressed){
    float currentSpeed = gg::Modulo(getXZVelocity());
    if(!_keyPressed && currentSpeed == 0)
        return;

    if(_keyPressed && currentSpeed < _max_speed) {    // If a key is pressed and we haven't reached max speed yet
        _force *= FORCE_FACTOR;
        applyCentralForce(_force);                       // Accelerate!
    }
    else if (currentSpeed > 2) {                                    // Any key is pressed, but the speed is higher than 2! We're moving
        _force = getVelocity() * gg::Vector3f(-0.08, 0, -0.08) * FORCE_FACTOR;
        applyCentralForce(_force);                       // Stopping!
    }
    else {                                                          // If we reach here, any key is pressed and the speed is below 2
        // Set it to 0
        setLinearVelocity(gg::Vector3f(0, getVelocity().Y, 0));
    }
}


void CRigidBody::activate(bool b){
    body->activate(b);
}

gg::Vector3f CRigidBody::getBodyPosition(){
    btTransform trans;
    body->getMotionState()->getWorldTransform(trans);

    return gg::Vector3f(
        static_cast<float>(trans.getOrigin().getX()),
        static_cast<float>(trans.getOrigin().getY()),
        static_cast<float>(trans.getOrigin().getZ())
    );
}

void CRigidBody::setBodyPosition(gg::Vector3f &_pos){
    btTransform trans;
    body->getMotionState()->getWorldTransform(trans);

    trans.setOrigin(btVector3(
        _pos.X,
        _pos.Y,
        _pos.Z
    ));
    body->getMotionState()->setWorldTransform(trans);
}

void CRigidBody::setOffsetBodyPosition(gg::Vector3f &_off){
    btTransform trans;
    body->getMotionState()->getWorldTransform(trans);

    trans.setOrigin(btVector3(
        trans.getOrigin().getX()+_off.X,
        trans.getOrigin().getY()+_off.Y,
        trans.getOrigin().getZ()+_off.Z
    ));
    body->getMotionState()->setWorldTransform(trans);
}

gg::Vector3f CRigidBody::getLinearVelocity(){
    return gg::Vector3f(
        static_cast<float>(body->getLinearVelocity().getX()),
        static_cast<float>(body->getLinearVelocity().getY()),
        static_cast<float>(body->getLinearVelocity().getZ())
    );
}

gg::Vector3f CRigidBody::getVelocity(){
    return gg::Vector3f(body->getLinearVelocity().getX(), body->getLinearVelocity().getY(), body->getLinearVelocity().getZ());
}
gg::Vector2f CRigidBody::getXZVelocity(){
    return gg::Vector2f(body->getLinearVelocity().getX(), body->getLinearVelocity().getZ());
}

bool CRigidBody::checkContactResponse(){
    return world->contactTest(body);
}

// ----------------------------------------------------------------------------------------------------------------------------
// Funciones del mapa
// ----------------------------------------------------------------------------------------------------------------------------
void CRigidBody::updateCTransformPosition(){
    btTransform trans;
    body->getMotionState()->getWorldTransform(trans);

    if(cTransform){
        cTransform->setPosition(getBodyPosition());

        // ROTASAO
        // if(body->getInvMass()){
        //     btQuaternion rot = trans.getRotation();
        //     float _X, _Y, _Z;
        //     rot.getEulerZYX(_Z,_Y,_X);
        //     cTransform->setRotation(
        //         gg::Vector3f(
        //             static_cast<float>(_X/PI*180),
        //             static_cast<float>(_Y/PI*180),
        //             static_cast<float>(_Z/PI*180)
        //         )
        //     );
        // }
    }
}

void CRigidBody::Upd_MoverObjeto(){
    ObjectManager *manager = Singleton<ObjectManager>::Instance();
    CClock *clock = static_cast<CClock*>(manager->getComponent(gg::CLOCK,getEntityID()));

    if(clock){
        if(clock->hasEnded()){
            gg::cout(" -- CLOCK END");
            manager->removeComponentFromEntity(gg::CLOCK,getEntityID());
            actualUpd = nullptr;

            Blackboard b;
            b.GLOBAL_removeData("DATA_"+std::to_string(getEntityID()));

        }
        else{
            // Update del clock
            if(body->isKinematicObject()){
                Blackboard b;
                BRbData *data = static_cast<BRbData*>(b.GLOBAL_getBData("DATA_"+std::to_string(getEntityID())));

                gg::Vector3f offset(data->getRbData().vX,data->getRbData().vY,data->getRbData().vZ);

                setOffsetBodyPosition(offset);
            }
        }
    }
    else{
        Blackboard b;
        BFloat *data = static_cast<BFloat*>(b.GLOBAL_getBData("DATA_"+std::to_string(getEntityID())+"_TIME"));

        float dur = data->getFloat();
        clock = new CClock();
        clock->startChrono(dur);
        gg::cout(" -- CLOCK INIT ON "+std::to_string(dur));
        manager->addComponentToEntity(clock,gg::CLOCK,getEntityID());

        b.GLOBAL_removeData("DATA_"+std::to_string(getEntityID())+"_TIME");
    }

}

gg::EMessageStatus CRigidBody::SavePreviousStatus(){
    Previous = Current;

    return gg::ST_TRUE;
}
gg::EMessageStatus CRigidBody::SaveCurrentStatus(){
    btTransform trans;
    body->getMotionState()->getWorldTransform(trans);

    Current.Position = getBodyPosition();

    return gg::ST_TRUE;
}
gg::EMessageStatus CRigidBody::Interpolate(const Message &_Tick){

    float Tick = *(static_cast<float*>(_Tick.mData));

    float X = Previous.Position.X *(1-Tick) + Current.Position.X*Tick;
    float Y = Previous.Position.Y *(1-Tick) + Current.Position.Y*Tick;
    float Z = Previous.Position.Z *(1-Tick) + Current.Position.Z*Tick;

    cTransform->setPosition(gg::Vector3f(X,Y,Z));
    return gg::ST_TRUE;
}


CRigidBody::Status::Status(){}
CRigidBody::Status::Status(const Status &orig){
    Position = orig.Position;
    Rotation = orig.Rotation;
}
CRigidBody::Status::~Status(){}
