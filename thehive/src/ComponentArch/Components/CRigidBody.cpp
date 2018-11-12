#include "CRigidBody.hpp"

CRigidBody::CRigidBody()
:cTransform(nullptr)
{

}

CRigidBody::~CRigidBody() {

}

void CRigidBody::initComponent() {
    //  Si necesitas punteros a otras funciones es importante suscribir esta componente al mensaje M_SETPTRS
    //  Este mensaje se llamará para recalular los punteros cuando se borre una componente de un objeto

    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::RIGID_BODY, gg::M_UPDATE);
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::RIGID_BODY, gg::M_SETPTRS);

}

void CRigidBody::initializeComponentData(const void* data){

    if(data){
        InitCRigidBody* cData = (InitCRigidBody*)data;

        // Puntero al mundo de fisicas
        world = Singleton<ggDynWorld>::Instance();

        if(cData->loadedFromPath){
            btBulletWorldImporter*  fileLoader = new btBulletWorldImporter(world->getDynamicsWorld());
            if(! ( fileLoader->loadFile(cData->path.c_str()) ) )
                return;

            // TODO:
            //      Cambio a bucle, por si fileLoader carga distintos cuerpos de colisiones?
            btCollisionObject* obj = fileLoader->getRigidBodyByIndex(0);
            body = btRigidBody::upcast(obj);
            shape = body->getCollisionShape();

        }
        else{
            shape = new btBoxShape(btVector3(btScalar(cData->sX), btScalar(cData->sY), btScalar(cData->sZ)));
        }

        // AQUI SE DEFINEN LAS DIMENSIONES
        // shape = new btBoxShape(btVector3(btScalar(cData->sX), btScalar(cData->sY), btScalar(cData->sZ)));

        // Hago pushback en el vector de 'shapes'
        world->addShape(shape);

        // AQUI SE DEFINE LA POSICION
        transform.setIdentity();
        transform.setOrigin(btVector3(cData->x,cData->y,cData->z));

        // MASS!=0 ---> RIGIDBODY ES DINAMICO
        // MASS==0 ---> RIGIDBODY ES ESTATICO
        btScalar mass(cData->mass);
        bool isDynamic = (mass != 0.f);
        // btVector3 localInertia(cData->iX,cData->iY,cData->iZ);
        btVector3 localInertia;
        if (isDynamic)
            shape->calculateLocalInertia(mass, localInertia);

        // Supongo que es algo que mejora las colisiones y opcional, PERO, sin el myMotionState NO SE PUEDE INICIALIZAR EL BODY =D
            // Using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
        btDefaultMotionState* myMotionState = new btDefaultMotionState(transform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, localInertia);
        body = new btRigidBody(rbInfo);

        // We apply the gravity of the world
        body->setGravity(btVector3(0,-10,0));
        body->applyGravity();

        // Add the body to the dynamics world
        world->addRigidBody(body);

    }
    engine = Singleton<GameEngine>::Instance();

    //  Inicializar punteros a otras compnentes
    MHandler_SETPTRS();
}


gg::EMessageStatus CRigidBody::processMessage(const Message &m) {

    if      (m.mType == gg::M_UPDATE)   return MHandler_UPDATE  ();
    else if (m.mType == gg::M_SETPTRS)  return MHandler_SETPTRS ();

    return gg::ST_ERROR;
}


//  Message handler functions_______________________________________________________________
//|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |

gg::EMessageStatus CRigidBody::MHandler_SETPTRS(){
    // Inicializando punteros
    cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));

    return gg::ST_TRUE;
}

gg::EMessageStatus CRigidBody::MHandler_UPDATE(){
    // UPDATE
    btTransform trans;
    body->getMotionState()->getWorldTransform(trans);

    if(cTransform){
        cTransform->setPosition(
            gg::Vector3f(
                static_cast<float>(trans.getOrigin().getX()),
                static_cast<float>(trans.getOrigin().getY()),
                static_cast<float>(trans.getOrigin().getZ())
            )
        );
    }

    return gg::ST_TRUE;
}

void CRigidBody::applyCentralImpulse(gg::Vector3f vec){
    body->applyCentralImpulse(btVector3(vec.X,vec.Y,vec.Z));
}

void CRigidBody::applyCentralForce(gg::Vector3f vec){
    body->applyCentralForce(btVector3(vec.X,vec.Y,vec.Z));
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
