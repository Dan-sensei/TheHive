#include "CFlock.hpp"
//#include "CRigidBody.hpp"
#include <iostream>

CFlock::CFlock(bool lider,uint16_t id):Manager(nullptr),leader(lider)
{
    Manager= Singleton<ObjectManager>::Instance();
    //leader=false;
    mindist=0.8;//minima distancia para aplica separacion 0.8 buena
    fuerzasep=20;//fuerza separacion
    fuerzacoh=10;//fuerza cohesion
    if(lider){
        addFlocked(id);
        leader_id=id;
    }

}
CFlock::CFlock()
{
}

CFlock::~CFlock(){

}
void CFlock::Muerte(){
    if(leader){
        removerFlocked(leader_id);
        //pasar el testigo
        //debugtotal();
        setNewLeader();



    }
    else{
        //eliminame de la lista papu
        CFlock* flock_lider = static_cast<CFlock*>(Manager->getComponent(gg::FLOCK,leader_id));
        flock_lider->removerFlocked(getEntityID());
    }
    //destruir esta entidad
    Manager->removeComponentFromEntity(gg::FLOCK,getEntityID() );

}
void CFlock::removerFlocked(int id){
    CRigidBody* body = static_cast<CRigidBody*>(Manager->getComponent(gg::RIGID_BODY,id));
    Flocked.remove(body);
/*
    if(Flocked.size()<=1){
        std::cout << "else" << '\n';
        auto it=Flocked.begin();
        //destruimos todo lo demas //implementar
        while (it!=Flocked.end()){
            CRigidBody* body2=*it;
            int id2=body2->getEntityID();
            Manager->removeComponentFromEntity(gg::FLOCK,id2 );
            it++;
        }

    }
    */

}

bool CFlock::getLeader(){
    return leader;
}

void CFlock::setNewLeader(){
    if(Flocked.size()>1){
        //ese es el puto lider
        auto it=Flocked.begin();
        CRigidBody* body=*it;
        int id=body->getEntityID();//WTF
        CFlock* flock_lider = static_cast<CFlock*>(Manager->getComponent(gg::FLOCK,id));
        flock_lider->setIAmLeader(true);
        flock_lider->setLeader(id);
        //pasarle la lista
        flock_lider->copyFlocked(leader_id);//esto o lo paso por parametro?
        it++;
        //informamos al resto del cambio de lider
        while (it!=Flocked.end()){
            CRigidBody* body2=*it;
            int id2=body2->getEntityID();
            CFlock* flock_bastardo = static_cast<CFlock*>(Manager->getComponent(gg::FLOCK,id2));
            flock_bastardo->setLeader(id);
            it++;
        }


    }

}
//flock_lider->copyFlocked(leader_id);

std::list  <CRigidBody*> CFlock::getFlocked(){
    return Flocked;
}
void CFlock::copyFlocked(int id){
    CFlock* flock_lider = static_cast<CFlock*>(Manager->getComponent(gg::FLOCK,id));
    Flocked=flock_lider->getFlocked();

}



//acaba destructor
void CFlock::Init(){
        //Manager= Singleton<ObjectManager>::Instance();

}
void CFlock::setLeader(int id){
    leader_id=id;
}
void CFlock::setIAmLeader(bool id){
    leader=id;
}
void CFlock::debugtotal(){
    auto it=Flocked.begin();
    std::cout << "tam" << '\n';
    std::cout << Flocked.size() << '\n';
    std::cout << "inicio" << '\n';
    while (it!=Flocked.end()){
        CRigidBody* body=*it;
        int id=body->getEntityID();
        std::cout << id << '\n';
        it++;
    }

    /*
    //std::cout << pos << '\n';
    gg::Vector3f media;
    while (it!=Flocked.end()){
        CRigidBody* body=*it;
        media+=body->getBodyPosition();
        std::cout << body->getBodyPosition() << '\n';
        it++;
    }
    media/=(Flocked.size());
    std::cout << "media" << '\n';
    std::cout << media << '\n';
    */
    std::cout << "fin" << '\n';

}
void CFlock::FixedUpdate(){

    if(leader){
        if(Flocked.size()<=1){
            Manager->removeComponentFromEntity(gg::FLOCK,getEntityID() );
        }
        //debugeando
        //debugtotal();

        //Separation
        FastSeparation();
        //El resto
        FastAlignementAndCohesion();
        //esto es codigo de swarm, basicamente para que a parte del flocking tengan todos un mismo destino
        //ForceCenter();
        //ChangeCenter();
        //Muerte();
    }
}
void CFlock::ChangeCenter(){
    //gg::Vector3f res;
    //res.X=gg::genFloatRandom(-0.5,0.5);
    //res.Y=gg::genFloatRandom(-0.5,0.5);
    //pos+=res;

}
void CFlock::ForceCenter(){
    /*
    auto it=Flocked.begin();
    while (it!=Flocked.end()){
        //std::cout << "entidad"<<i << '\n';
        CRigidBody* body=*it;


        gg::Vector3f dir=gg::Normalice(pos-body->getBodyPosition());
        dir=dir*20;
        //std::cout << "dir=" <<dir<< '\n';
        body->applyCentralForce(dir);


        it++;
    }
*/
}
void CFlock::addNewFlocked(uint16_t me){
    CFlock* cFlock = new CFlock(false);
    Manager->addComponentToEntity(cFlock, gg::FLOCK, me);
    cFlock->setLeader(leader_id);
    //setlista
    addFlocked(me);
}
void CFlock::addFlocked(uint16_t me){
    Manager= Singleton<ObjectManager>::Instance();

    CRigidBody* body = static_cast<CRigidBody*>(Manager->getComponent(gg::RIGID_BODY,me));
    Flocked.push_back(body);
}


void CFlock::FastSeparation(){
    mediapos=gg::Vector3f();
    mediavel=gg::Vector3f();
    //int i=0;
    auto it=Flocked.begin();
    while (it!=Flocked.end()){
        //std::cout << "entidad"<<i << '\n';
        CRigidBody* body=*it;
        //calculamos las dos medias
        mediavel+=body->getVelocity();
        mediapos+=body->getBodyPosition();
        //Separation
        auto it2=Flocked.begin();
        while (it2!=Flocked.end()){
            CRigidBody* body2=*it2;
            if(body!=body2){
                //mindist
                float dist=gg::FastDIST(body->getBodyPosition(), body2->getBodyPosition());
                if(dist<mindist){
                    //std::cout << "aplicamos" << '\n';
                    //std::cout << "dist="<<dist << '\n';
                    //std::cout << "mindist="<<mindist << '\n';
                    //aplicamos la separation
                    gg::Vector3f dir=gg::Normalice(body->getBodyPosition()-body2->getBodyPosition());
                    float escala=1-sqrt(dist/mindist);
                    dir=dir*escala*fuerzasep;
                    //std::cout << "dir=" <<dir<< '\n';
                    body->applyCentralForce(dir);
                }
            }

            it2++;
        }

        it++;
        //i++;
    }

}
void CFlock::FastAlignementAndCohesion(){
    auto it=Flocked.begin();
    while (it!=Flocked.end()){
        CRigidBody* body=*it;
        //alignement aun no implementado
        gg::Vector3f mediavel_real=(mediavel-body->getVelocity()/(Flocked.size()-1));
        //std::cout << mediavel_real << '\n';
        //utilizar la media de las velicidades para alinearlo
        //cohesion
        gg::Vector3f mediapos_real=((mediapos-body->getBodyPosition())/(Flocked.size()-1));
        //std::cout << "media real" << '\n';
        //std::cout << mediapos_real << '\n';
        gg::Vector3f dir=gg::Normalice(mediapos_real-body->getBodyPosition());
        dir=dir*fuerzacoh;
        body->applyCentralForce(dir);
        it++;
    }

}
