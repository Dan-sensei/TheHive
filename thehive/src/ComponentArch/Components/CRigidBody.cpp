#include "CRigidBody.hpp"
#include <vector>

#define PI 3.14159265359

std::vector<const char*> names;

CRigidBody::CRigidBody()
:cTransform(nullptr)
{
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
        // for(int i=0 ; i<fileLoader->getNumBvhs() ; i++){
        //     // Lo borro cuando CRigidBody se destruya
        //     delete fileLoader->getBvhByIndex(i);
        // }
        // for(int i=0 ; i<fileLoader->getNumConstraints() ; i++){
        //     delete fileLoader->getConstraintByIndex(i);
        // }
        // for(int i=0 ; i<fileLoader->getNumTriangleInfoMaps() ; i++){
        //     delete fileLoader->getTriangleInfoMapByIndex(i);
        // }
        // for(int i=0 ; i<fileLoader->getNumRigidBodies() ; i++){
        //     btCollisionObject* _obj = fileLoader->getRigidBodyByIndex(i);
        //     btRigidBody* _body = btRigidBody::upcast(_obj);
        //     // if(_body && _body->getMotionState()){
        //     //     delete _body->getMotionState();
        //     // }
        //     world->removeCollisionObject(_obj);
        //     delete _obj;
        // }
        // for(int i=0 ; i<fileLoader->getNumCollisionShapes() ; i++){
        //     // delete fileLoader->getCollisionShapeByIndex(i);
        // }
        // std::cout << "AFTER-----------" << '\n';
        // std::cout << "Bvhs:             " << fileLoader->getNumBvhs() << '\n';
        // std::cout << "Constraints:      " << fileLoader->getNumConstraints() << '\n';
        // std::cout << "TriangleInfoMaps: " << fileLoader->getNumTriangleInfoMaps() << '\n';
        // std::cout << "RigidBodies:      " << fileLoader->getNumRigidBodies() << '\n';
        // std::cout << "CollisionShapes:  " << fileLoader->getNumCollisionShapes() << '\n';
        // delete obj;
        fileLoader->deleteAllData();
        delete fileLoader;
        // fileLoader = nullptr;
        // --------------------
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
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::RIGID_BODY, gg::M_XPLOTATO);

}

void CRigidBody::initializeComponentData(const void* data){

    if(data){
        InitCRigidBody* cData = (InitCRigidBody*)data;

        // Puntero al mundo de fisicas
        world = Singleton<ggDynWorld>::Instance();

        fileLoader = nullptr;

        if(cData->loadedFromPath){
            fileLoader = new btBulletWorldImporter();
            if(! ( fileLoader->loadFile(cData->path.c_str())) ){
                return;
            }

            btCollisionObject* obj = fileLoader->getRigidBodyByIndex(0);
            body = btRigidBody::upcast(obj);
            shape = body->getCollisionShape();

            // ------------------------

            transform = obj->getWorldTransform();

            transform.setOrigin(btVector3(cData->x,cData->y,cData->z));
            myMotionState = new btDefaultMotionState(transform);
            body->setMotionState(myMotionState);

            // Hago pushback en el vector de 'shapes'
            world->addShape(shape);

            // MASS!=0 ---> RIGIDBODY ES DINAMICO
            // MASS==0 ---> RIGIDBODY ES ESTATICO
            btScalar mass(cData->mass);
            bool isDynamic = (mass != 0.f);
            btVector3 localInertia;
            if (isDynamic)
            shape->calculateLocalInertia(mass, localInertia);

            // Supongo que es algo que mejora las colisiones y opcional, PERO, sin el myMotionState NO SE PUEDE INICIALIZAR EL BODY =D
            // Using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
            btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, localInertia);
            body = new btRigidBody(rbInfo);

            if(cData->friction){
                body->setFriction(btScalar(cData->friction));
            }

            world->setGravity(0,-200,0);

            // Add the body to the dynamics world
            world->addRigidBody(body);
        }
        else{
            shape = new btBoxShape(btVector3(btScalar(cData->sX), btScalar(cData->sY), btScalar(cData->sZ)));

            transform.setIdentity();
            transform.setOrigin(btVector3(cData->x,cData->y,cData->z));
            myMotionState = new btDefaultMotionState(transform);

            // Hago pushback en el vector de 'shapes'
            world->addShape(shape);

            // MASS!=0 ---> RIGIDBODY ES DINAMICO
            // MASS==0 ---> RIGIDBODY ES ESTATICO
            btScalar mass(cData->mass);
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

            if(cData->friction){
                body->setFriction(btScalar(cData->friction));
            }

            world->setGravity(0,-200,0);

            // Add the body to the dynamics world
            world->addRigidBody(body);
        }
    }

    //  Inicializar punteros a otras compnentes
    MHandler_SETPTRS();
}


gg::EMessageStatus CRigidBody::processMessage(const Message &m) {

    if      (m.mType == gg::M_UPDATE)       return MHandler_UPDATE  ();
    else if (m.mType == gg::M_XPLOTATO)     return MHandler_XPLOTATO(m);
    else if (m.mType == gg::M_SETPTRS)      return MHandler_SETPTRS ();

    return gg::ST_ERROR;
}


//  Message handler functions_______________________________________________________________
//|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |

gg::EMessageStatus CRigidBody::MHandler_XPLOTATO(const Message &m){
    if(m.mData){
        TriggerRecordStruct* cdata=(TriggerRecordStruct*)m.mData;
        if(cTransform){
            //cTransform->getBodyPosition();//v1
            //std::cout << "empieza" << '\n';
            //gg::Vector3f v1=cTransform->getPosition();
            //std::cout << "v1: "<< v1 << '\n';
            //gg::Vector3f v2=cdata->vPos;
            //std::cout << "v2: "<< v2 << '\n';

            //cdata->vPos;//v2
            float distancia=gg::DIST(cTransform->getPosition(),cdata->vPos);
            ////float ratio=1-distancia/fRadius;
            //std::cout << "distancia: "<<distancia << '\n';
            //std::cout << "v1-v2: "<< v1-v2 << '\n';
            //std::cout << "normalizado(v1-v2): "<< gg::Normalice(v1-v2) << '\n';
            //gg::Vector3f v3=gg::Normalice(v1-v2);

            //std::cout << "modv3: "<<gg::Modulo(v3)  << '\n';

            //std::cout << "ratio: "<< (1-distancia/cdata->fRadius) << '\n';


            float fuerzabomba=80000;
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
            std::cout << "antes" <<suma.X<<suma.Y<<suma.Z<< '\n';
            gg::Normalice(vect);
            *///pruebas
            //body->applyCentralForce(btVector3(0,46000000,0));
        }
    }
    return gg::ST_TRUE;
}

gg::EMessageStatus CRigidBody::MHandler_SETPTRS(){
    // Inicializando punteros
    cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));

    return gg::ST_TRUE;
}

gg::EMessageStatus CRigidBody::MHandler_UPDATE(){
    // UPDATE
    // body->activate(true);

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

        if(body->getInvMass()){
            btQuaternion rot = trans.getRotation();
            float _X, _Y, _Z;
            rot.getEulerZYX(_Z,_Y,_X);
            cTransform->setRotation(
                gg::Vector3f(
                    static_cast<float>(_X/PI*180),
                    static_cast<float>(_Y/PI*180),
                    static_cast<float>(_Z/PI*180)
                )
            );
        }

    }

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
