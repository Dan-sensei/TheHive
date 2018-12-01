#include "CRigidBody.hpp"
#include <vector>

#include "CTransform.hpp"
#include "CClock.hpp"

#define PI 3.14159265359
#define FORCE_FACTOR    200.f

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
        // std::cout << "Bvhs:             " << fileLoader->getNumBvhs() << '\n';
        // std::cout << "Constraints:      " << fileLoader->getNumConstraints() << '\n';
        // std::cout << "TriangleInfoMaps: " << fileLoader->getNumTriangleInfoMaps() << '\n';
        // std::cout << "RigidBodies:      " << fileLoader->getNumRigidBodies() << '\n';
        // std::cout << "CollisionShapes:  " << fileLoader->getNumCollisionShapes() << '\n';
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

CRigidBody::~CRigidBody() {
    delete myMotionState;
    world->removeRigidBody(body);
    delete body;

    // --------------------
    // Delete de todo lo que he creado con el loadfile
    // std::cout << "BEFORE----------" << '\n';
    // std::cout << "Bvhs:             " << fileLoader->getNumBvhs() << '\n';
    // std::cout << "Constraints:      " << fileLoader->getNumConstraints() << '\n';
    // std::cout << "TriangleInfoMaps: " << fileLoader->getNumTriangleInfoMaps() << '\n';
    // std::cout << "RigidBodies:      " << fileLoader->getNumRigidBodies() << '\n';
    // std::cout << "CollisionShapes:  " << fileLoader->getNumCollisionShapes() << '\n';

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

void CRigidBody::initComponent() {
    //  Si necesitas punteros a otras funciones es importante suscribir esta componente al mensaje M_SETPTRS
    //  Este mensaje se llamará para recalular los punteros cuando se borre una componente de un objeto

    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::RIGID_BODY, gg::M_UPDATE);
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::RIGID_BODY, gg::M_SETPTRS);
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::RIGID_BODY, gg::M_EVENT_ACTION);
    //Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::RIGID_BODY, gg::M_XPLOTATO);

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

    if      (m.mType == gg::M_UPDATE)               return MHandler_UPDATE      ();
    //else if (m.mType == gg::M_XPLOTATO)     return MHandler_XPLOTATO(m);
    else if (m.mType == gg::M_SETPTRS)              return MHandler_SETPTRS     ();
    else if (m.mType == gg::M_EVENT_ACTION)         return MHandler_DOACTION    (m);

    return gg::ST_ERROR;
}


//  Message handler functions_______________________________________________________________
//|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |

gg::EMessageStatus CRigidBody::MHandler_DOACTION(Message _mes){
    int *action = static_cast<int*>(_mes.mData);
    // gg::cout("ACTION: "+std::to_string(*action));

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
        //cdata->vPos;//v2
        float distancia=gg::DIST(cTransform->getPosition(),cdata->vPos);
        ////float ratio=1-distancia/fRadius;
        //std::cout << "distancia: "<<distancia << '\n';
        //std::cout << "v1-v2: "<< v1-v2 << '\n';
        //std::cout << "normalizado(v1-v2): "<< gg::Normalice(v1-v2) << '\n';
        //gg::Vector3f v3=gg::Normalice(v1-v2);

        //std::cout << "modv3: "<<gg::Modulo(v3)  << '\n';

        //std::cout << "ratio: "<< (1-distancia/cdata->fRadius) << '\n';


        float fuerzabomba=cdata->data.find(kDat_damage);
        gg::Vector3f sol =
            gg::Normalice(cTransform->getPosition()-cdata->vPos)
            *fuerzabomba*
            (1-distancia/cdata->fRadius);
        applyCentralForce(sol);
        //gg::Vector3f vect(33,66,99);
//std::cout << vect << '\n';
        /*
        gg::Vector3f vect(33,66,99);
        gg::Vector3f vect2(33,66,99);

        gg::Vector3f suma=vect*vect2;
        //std::cout << "antes" <<suma.X<<suma.Y<<suma.Z<< '\n';
        gg::Normalice(vect);
        *///pruebas
        //body->applyCentralForce(btVector3(0,46000000,0));
    }
}

gg::EMessageStatus CRigidBody::MHandler_SETPTRS(){
    // Inicializando punteros
    cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));

    return gg::ST_TRUE;
}

gg::EMessageStatus CRigidBody::MHandler_UPDATE(){
    // UPDATE
    body->activate(true);

    if(actualUpd)
        (this->*actualUpd)();
    updateCTransformPosition();

    return gg::ST_TRUE;
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

// ----------------------------------------------------------------------------------------------------------------------------
// Funciones del mapa
// ----------------------------------------------------------------------------------------------------------------------------
void CRigidBody::updateCTransformPosition(){
    btTransform trans;
    body->getMotionState()->getWorldTransform(trans);

    if(cTransform){
        cTransform->setPosition(getBodyPosition());

        // if(getEntityID()==11){
        //     gg::cout(
        //         " -- POS-T -> ("+std::to_string(cTransform->getPosition().X)+
        //         ","+std::to_string(cTransform->getPosition().Y)+
        //         ","+std::to_string(cTransform->getPosition().Z)+")"
        //     );
        //     gg::cout(
        //         " -- POS-B -> ("+std::to_string(trans.getOrigin().getX())+
        //         ","+std::to_string(trans.getOrigin().getY())+
        //         ","+std::to_string(trans.getOrigin().getZ())+")"
        //     );
        // }


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
            // gg::cout(" -- CLOCK DUR -> "+std::to_string(clock->getActualTime()));
            if(body->isKinematicObject()){
                Blackboard b;
                BRbData *data = static_cast<BRbData*>(b.GLOBAL_getBData("DATA_"+std::to_string(getEntityID())));

                // gg::cout(
                //     "("+std::to_string(rbS.vX)+
                //     ","+std::to_string(rbS.vY)+
                //     ","+std::to_string(rbS.vZ)+")"
                // );

                btTransform trans;
                body->getMotionState()->getWorldTransform(trans);

                trans.setOrigin(btVector3(
                    trans.getOrigin().getX()+data->getRbData().vX,
                    trans.getOrigin().getY()+data->getRbData().vY,
                    trans.getOrigin().getZ()+data->getRbData().vZ
                ));

                body->getMotionState()->setWorldTransform(trans);
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
