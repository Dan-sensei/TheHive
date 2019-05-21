#include "CRigidBody.hpp"
#include <vector>

#include "CTransform.hpp"
#include "CClock.hpp"
#include <ComponentArch/Components/CStaticModel.hpp>

#define PI                  3.14159265359f
#define FORCE_FACTOR        400.f
#define GRAVITY             -15.f

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
    //unsigned int Group,
    //unsigned int Mask
)
:cTransform(nullptr), cStaticModel(nullptr),world(nullptr)
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
        //world->addRigidBody(body,Group,Mask);
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
        //world->addRigidBody(body,Group,Mask);
    }

    if(kinematic){
        // CF_KINEMATIC_OBJECT = 2
        body->setCollisionFlags(2);
    }

    body->setAngularFactor(btVector3(0,0,0));
    SaveCurrentStatus();
    SavePreviousStatus();
}

CRigidBody::CRigidBody(
    bool kinematic,
    float x,float y,float z,
    float sX,float sY,float sZ)
:cTransform(nullptr), cStaticModel(nullptr),world(nullptr)
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

    // CF_NO_CONTACT_RESPONSE = 4
    body->setCollisionFlags( body->getCollisionFlags() | 4);

    // Add the body to the dynamics world
    world->addRigidBody(body);
    SaveCurrentStatus();
    SavePreviousStatus();
}

CRigidBody::CRigidBody(
    float x, float y, float z,
    float rx, float ry, float rz, float rw,
    float sX, float sY, float sZ
)
:cTransform(nullptr), cStaticModel(nullptr),world(nullptr)
{
    world = Singleton<ggDynWorld>::Instance();
    fileLoader = nullptr;

    shape = new btBoxShape(btVector3(btScalar(sX), btScalar(sY), btScalar(sZ)));

    transform.setIdentity();
    transform.setOrigin(btVector3(x,y,z));
    transform.setRotation(btQuaternion(rx, ry, rz, rw));
    myMotionState = new btDefaultMotionState(transform);

    world->addShape(shape);

    btScalar mass(10);
    bool isDynamic = (mass != 0.f);
    btVector3 localInertia;

    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, localInertia);
    body = new btRigidBody(rbInfo);
    //body->setCenterOfMassTransform(transform);

    body->setCollisionFlags(2);

    body->setFriction(btScalar(0.2));

    world->addRigidBody(body);
    // body->setAngularFactor(btVector3(0,0,0));
    SaveCurrentStatus();
    SavePreviousStatus();
}

CRigidBody::~CRigidBody() {
    if(myMotionState)   delete myMotionState;
    world->removeRigidBody(body);
    if(body)            delete body;

    // --------------------
    // Delete de todo lo que he creado con el loadfile

    if(fileLoader){
        fileLoader->deleteAllData();
        delete fileLoader;
    }
    else{
        // Cuando no carga desde fichero
        // Borrar la boxshape que se ha creado
        if(shape)       delete shape;
    }
}

void CRigidBody::Init(){
    world->setGravity(0,GRAVITY,0);

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
        float distancia=glm::distance(cTransform->getPosition(),cdata->vPos);
        float fuerzabomba=cdata->data.find(kDat_Damage);
        //std::cout << "fuerza" <<fuerzabomba<< '\n';
        glm::vec3 sol =glm::normalize(cTransform->getPosition()-cdata->vPos)*fuerzabomba*(1-distancia/cdata->fRadius);
        //std::cout << "VEC:(" <<sol.x<<","<<sol.y<<","<<sol.z<<")"<< '\n';
        applyCentralForce(sol);
    }
}

gg::EMessageStatus CRigidBody::MHandler_SETPTRS(){
    // Inicializando punteros
    cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));
    cStaticModel = static_cast<CStaticModel*>(Singleton<ObjectManager>::Instance()->getComponent(gg::STATICMODEL, getEntityID()));

    return gg::ST_TRUE;
}

void CRigidBody::FixedUpdate(){
    // UPDATE

    // COPIA-PEGA DE LA DOCUMENTACION:
    // Bullet automatically deactivates dynamic rigid bodies, when the velocity is below a threshold for a given time.
    // Deactivated (sleeping) rigid bodies don't take any processing time, except a minor broadphase collision detection impact
    // (to allow active objects to activate/wake up sleeping objects)
    body->activate(true);

    if(actualUpd)
        (this->*actualUpd)();
    //updateCTransformPosition();
}

void CRigidBody::applyCentralImpulse(glm::vec3 vec){
    body->applyCentralImpulse(btVector3(vec.x,vec.y,vec.z));
}

void CRigidBody::clearForce(){
    body->clearForces();
}
void CRigidBody::applyCentralForce(glm::vec3 vec){
    body->applyCentralForce(btVector3(vec.x,vec.y,vec.z));
}

void CRigidBody::applyTorque(glm::vec3 vec){
    body->applyTorque(btVector3(vec.x,vec.y,vec.z));
}

void CRigidBody::setLinearVelocity(glm::vec3 vec){
    body->setLinearVelocity(btVector3(vec.x,vec.y,vec.z));
}

void CRigidBody::applyConstantVelocityNormal(glm::vec3 _force,float _max_speed){
    if(glm::length(getXZVelocity()) < _max_speed)
        applyCentralForce(_force*(FORCE_FACTOR/2)*_max_speed);

}
void CRigidBody::applyConstantVelocity(glm::vec3 _force,float _max_speed,bool _keyPressed){
    float currentSpeed = glm::length(getXZVelocity());
    if(!_keyPressed && currentSpeed == 0)
        return;

    if(_keyPressed && currentSpeed < _max_speed) {    // If a key is pressed and we haven't reached max speed yet
        if(!body->isKinematicObject()){
            _force *= FORCE_FACTOR;
            applyCentralForce(_force);                       // Accelerate!
        }
        else{
            setOffsetBodyPosition(_force);
        }
    }
    else if (currentSpeed > 2) {                                    // Any key is pressed, but the speed is higher than 2! We're moving
        if(!body->isKinematicObject()) {
            applyCentralForce(_force);                       // Stopping!
            _force = getVelocity() * glm::vec3(-0.2, 0, -0.2) * FORCE_FACTOR;
        }
        else{
            setOffsetBodyPosition(_force);
        }
    }
    else {                                                          // If we reach here, any key is pressed and the speed is below 2
        // Set it to 0
        setLinearVelocity(glm::vec3(0, getVelocity().y, 0));
    }
}


void CRigidBody::activate(bool b){
    body->activate(b);
}
btRigidBody* CRigidBody::getBody(){
    return body;
}
glm::vec3 CRigidBody::getBodyPosition(){
    btTransform trans;
    body->getMotionState()->getWorldTransform(trans);

    return glm::vec3(
        static_cast<float>(trans.getOrigin().getX()),
        static_cast<float>(trans.getOrigin().getY()),
        static_cast<float>(trans.getOrigin().getZ())
    );
}

void CRigidBody::setBodyPosition(glm::vec3 &_pos){
    btTransform trans;
    body->getMotionState()->getWorldTransform(trans);

    trans.setOrigin(btVector3(
        _pos.x,
        _pos.y,
        _pos.z
    ));
    body->getMotionState()->setWorldTransform(trans);

    // btVector3 pos = body->getWorldTransform().getOrigin();
    // body->getWorldTransform().setOrigin(btVector3(_pos.x,_pos.y,_pos.z));
}

void CRigidBody::setNotKinematicBodyPosition(glm::vec3 &_pos){
    body->getWorldTransform().setOrigin(btVector3(_pos.x,_pos.y,_pos.z));
}

void CRigidBody::setOffsetBodyPosition(glm::vec3 &_off){
    btTransform trans;
    body->getMotionState()->getWorldTransform(trans);

    trans.setOrigin(btVector3(
        trans.getOrigin().getX()+_off.x,
        trans.getOrigin().getY()+_off.y,
        trans.getOrigin().getZ()+_off.z
    ));
    body->getMotionState()->setWorldTransform(trans);

    // btVector3 pos = body->getWorldTransform().getOrigin();
    // body->getWorldTransform().setOrigin(pos + btVector3(_off.x,_off.y,_off.z));
}

void CRigidBody::setYPosition(const float &Y){
    btTransform trans;
    body->getMotionState()->getWorldTransform(trans);
    btVector3 _pos = body->getWorldTransform().getOrigin();

    trans.setOrigin(btVector3(
        _pos.getX(),
        Y,
        _pos.getZ()
    ));
    body->getMotionState()->setWorldTransform(trans);
}

void CRigidBody::setXZPosition(const float &X, const float &Z){
    btTransform trans;
    body->getMotionState()->getWorldTransform(trans);
    btVector3 _pos = body->getWorldTransform().getOrigin();

    trans.setOrigin(btVector3(
        X,
        _pos.getY(),
        Z
    ));
    body->getMotionState()->setWorldTransform(trans);
}

void CRigidBody::setGhostObject(){
    body->setCollisionFlags( body->getCollisionFlags() | 4);
}

void CRigidBody::deactivateGravity(){
    body->setGravity(btVector3(0,0,0));
}

void CRigidBody::activateGravity(){
    body->setGravity(btVector3(0,GRAVITY,0));
}


glm::vec3 CRigidBody::getLinearVelocity(){
    return glm::vec3(
        static_cast<float>(body->getLinearVelocity().getX()),
        static_cast<float>(body->getLinearVelocity().getY()),
        static_cast<float>(body->getLinearVelocity().getZ())
    );
}

glm::vec3 CRigidBody::getVelocity(){
    return glm::vec3(body->getLinearVelocity().getX(), body->getLinearVelocity().getY(), body->getLinearVelocity().getZ());
}
glm::vec2 CRigidBody::getXZVelocity(){
    return glm::vec2(body->getLinearVelocity().getX(), body->getLinearVelocity().getZ());
}

bool CRigidBody::checkContactResponse(){
    return world->contactTest(body);
}

bool CRigidBody::checkContactResponse(CRigidBody *objB){
    return world->contactTest(body,objB->body);
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
        //         glm::vec3(
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
            //gg::cout(" -- CLOCK END");
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

                glm::vec3 offset(data->getRbData().vX,data->getRbData().vY,data->getRbData().vZ);
                setOffsetBodyPosition(offset);

                if(cTransform){
                    // //std::cout << "cetransform" << '\n';

                }
                else if(cStaticModel){
                    // //std::cout << "cestaticmodel" << '\n';
                    cStaticModel->setPosition(getBodyPosition());
                }

            }
        }
    }
    else{
        Blackboard b;
        BFloat *data = static_cast<BFloat*>(b.GLOBAL_getBData("DATA_"+std::to_string(getEntityID())+"_TIME"));

        float dur = data->getFloat();
        clock = new CClock();
        clock->startChrono(dur);
        //gg::cout(" -- CLOCK INIT ON "+std::to_string(dur));
        manager->addComponentToEntity(clock,gg::CLOCK,getEntityID());

        b.GLOBAL_removeData("DATA_"+std::to_string(getEntityID())+"_TIME");
    }

}

void CRigidBody::setVirtualRotation(const glm::quat &Quaternion){
    Current.Rotation = Quaternion * Current.Rotation;
}
glm::quat CRigidBody::getVirtualRotation(){
    return Current.Rotation;
}


void CRigidBody::setRotY(float _y){
    glm::vec3 y      = glm::vec3(0,1,0);
    auto res= glm::angleAxis(glm::radians(_y), y);

    Current.Rotation=res;

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
gg::EMessageStatus CRigidBody::Interpolate(const Message &_Tick) {
    if(!cTransform) return gg::ST_TRUE;
    double Tick = *static_cast<double*>(_Tick.mData);

    // float X = Previous.Position.x *(1-Tick) + Current.Position.x*Tick;
    // float Y = Previous.Position.y *(1-Tick) + Current.Position.y*Tick;
    // float Z = Previous.Position.z *(1-Tick) + Current.Position.z*Tick;

    cTransform->setPosition(glm::mix(Previous.Position, Current.Position, static_cast<float>(Tick)));
    cTransform->setRotation(glm::slerp(Previous.Rotation, Current.Rotation, static_cast<float>(Tick)));

    return gg::ST_TRUE;
}


CRigidBody::Status::Status()
:Rotation(1,0,0,0)
{}
CRigidBody::Status::Status(const Status &orig){
    Position = orig.Position;
    Rotation = orig.Rotation;
}
CRigidBody::Status::~Status(){}
