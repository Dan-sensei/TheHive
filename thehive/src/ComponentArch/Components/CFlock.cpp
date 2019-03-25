#include "CFlock.hpp"
//#include "CRigidBody.hpp"
//#include <iostream>

CFlock::CFlock(bool lider,float _mindist,float _fuerzasep,float _fuerzacoh,float _fuerzaalign,uint16_t id)
:Manager(nullptr),leader(lider), mindist(_mindist), fuerzasep(_fuerzasep), fuerzacoh(_fuerzacoh), fuerzaalign(_fuerzaalign),bill(0,0,0,"assets/HUD/Botonsolo.png")
{
    Manager= Singleton<ObjectManager>::Instance();
    //leader=false;
    //BillboardBueno::BillboardBueno(0,0,0,"assets/HUD/Botonsolo.png");

    if(lider){
        addFlocked(id);
        leader_id=id;
    }

}
CFlock::CFlock():bill(0,0,0,"assets/HUD/Botonsolo.png")
{
}

CFlock::~CFlock(){

}
void CFlock::Muerte(){
    ////std::cout << "muero" << '\n';
    ////std::cout << "mi id es" <<getEntityID()<< '\n';
    ////std::cout << "antes" << '\n';
    //CFlock* prueba = static_cast<CFlock*>(Manager->getComponent(gg::FLOCK,leader_id));
    //prueba->debugtotal();

    if(leader){
        ////std::cout << "soy lider" << '\n';
        removerFlocked(leader_id);
        //pasar el testigo
        //debugtotal();
        setNewLeader();



    }
    else{
        ////std::cout << "no soy lider" << '\n';
        //eliminame de la lista papu
        CFlock* flock_lider = static_cast<CFlock*>(Manager->getComponent(gg::FLOCK,leader_id));
        flock_lider->removerFlocked(getEntityID());
    }
    //destruir esta entidad
    //CFlock* prueba2 = static_cast<CFlock*>(Manager->getComponent(gg::FLOCK,leader_id));
    ////std::cout << "despues" << '\n';
    //prueba2->debugtotal();
    Manager->removeComponentFromEntity(gg::FLOCK,getEntityID() );
    ////std::cout << "muero final" << '\n';


}
void CFlock::removerFlocked(int id){
    CRigidBody* body = static_cast<CRigidBody*>(Manager->getComponent(gg::RIGID_BODY,id));
    Flocked.remove(body);
/*
    if(Flocked.size()<=1){
        //std::cout << "else" << '\n';
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
    if(Flocked.size()>0){
        //ese es el puto lider
        auto it=Flocked.begin();
        CRigidBody* body=*it;
        int id=body->getEntityID();//WTF
        ////std::cout << "elegimos" <<id<< '\n';
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
    //else{
    //    //std::cout << "no elegimos" << '\n';
    //}

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
    //std::cout << "tam" << '\n';
    //std::cout << Flocked.size() << '\n';
    //std::cout << "inicio" << '\n';
    while (it!=Flocked.end()){
        CRigidBody* body=*it;
        int id=body->getEntityID();
        //std::cout << id << '\n';
        it++;
    }

    /*
    ////std::cout << pos << '\n';
    glm::vec3 media;
    while (it!=Flocked.end()){
        CRigidBody* body=*it;
        media+=body->getBodyPosition();
        //std::cout << body->getBodyPosition() << '\n';
        it++;
    }
    media/=(Flocked.size());
    //std::cout << "media" << '\n';
    //std::cout << media << '\n';
    */
    //std::cout << "fin" << '\n';

}
void CFlock::FixedUpdate(){
    if(leader){
        if(Flocked.size()<=1){
            ////std::cout << "eliminamos todo" << '\n';
            Manager->removeComponentFromEntity(gg::FLOCK,getEntityID() );
        }
        else{
            //CRigidBody* body = static_cast<CRigidBody*>(Manager->getComponent(gg::RIGID_BODY,leader_id));
            //auto pos=body->getBodyPosition();
            //std::cout << "Pos lider: (" <<pos.x<<","<<pos.y<<","<<pos.z<<")"<< '\n';
            //bill.setPos(pos.x,pos.y+10,pos.z);
            //bill.Draw();
            //Separation
            FastSeparation();
            //El resto
            FastAlignementAndCohesion();
        }
    }

}

void CFlock::addNewFlocked(uint16_t me){
    CFlock* cFlock = new CFlock(false,mindist, fuerzasep, fuerzacoh, fuerzaalign);
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

int CFlock::getLeaderID(){
    return leader_id;
}
void CFlock::FastSeparation(){
    mediapos=glm::vec3();
    mediavel=glm::vec3();
    auto it=Flocked.begin();
    while (it!=Flocked.end()){
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
                    //aplicamos la separation
                    glm::vec3 dir  = body->getBodyPosition()-body2->getBodyPosition();
                    if(!(dir.x==0 &&dir.z==0)){
                        dir=glm::normalize(dir);
                        float escala=1-sqrt(dist/mindist);
                        dir=dir*escala*fuerzasep;
                        body->applyCentralForce(dir);

                    }
                }
            }

            it2++;
        }

        it++;
    }

}
void CFlock::FastAlignementAndCohesion(){
    auto it=Flocked.begin();
    while (it!=Flocked.end()){
        CRigidBody* body=*it;
        //alignement
        float size = (Flocked.size()-1);
        glm::vec3 mediavel_real=((mediavel-body->getVelocity())/size);
        //body->applyCentralForce(mediavel_real);
        //cohesion
        glm::vec3 mediapos_real=((mediapos-body->getBodyPosition())/size);
        glm::vec3 dir  = mediapos_real-body->getBodyPosition();
        if(!(dir.x==0 &&dir.z==0)){
            dir=glm::normalize(mediapos_real-body->getBodyPosition());
            dir=dir*fuerzacoh;
            body->applyCentralForce(dir);
        }
        it++;
    }

}
