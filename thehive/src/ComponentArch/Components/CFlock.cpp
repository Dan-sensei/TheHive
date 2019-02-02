#include "CFlock.hpp"
//#include "CRigidBody.hpp"
#include <iostream>

CFlock::CFlock(gg::Vector3f _pos):pos(_pos)
{
}
CFlock::CFlock()
{
}

CFlock::~CFlock(){}

void CFlock::Init(){
        mindist=0.8;//minima distancia para aplica separacion
        fuerzasep=20;//fuerza separacion
        fuerzacoh=10;//fuerza cohesion
        Manager= Singleton<ObjectManager>::Instance();

}
void CFlock::debugtotal(){
    auto it=Flocked.begin();

//
//CRigidBody* body3=*it;
//it++;
////it++;
//CRigidBody* body4=*it;
//float pod =gg::FastDIST(body4->getBodyPosition(), body3->getBodyPosition());
//std::cout << "posicion" << '\n';
//std::cout << pod << '\n';

//

    std::cout << "tam" << '\n';
    std::cout << Flocked.size() << '\n';
    std::cout << "inicio y centro" << '\n';
    std::cout << pos << '\n';
    gg::Vector3f media;
    while (it!=Flocked.end()){
        CRigidBody* body=*it;
        media+=body->getBodyPosition();
        std::cout << body->getBodyPosition() << '\n';
        //std::cout << id << '\n';
        it++;
    }
    media/=(Flocked.size());
    std::cout << "media" << '\n';
    std::cout << media << '\n';
    std::cout << "fin" << '\n';

}
void CFlock::FixedUpdate(){
    //debugeando
    //debugtotal();

    //Separation
    //std::cout << "empieza separation" << '\n';
    FastSeparation();
    //std::cout << "mediaopos" << '\n';
    //std::cout << mediapos << '\n';
    //El resto
    //std::cout << "empieza el resto" << '\n';
    FastAlignementAndCohesion();
    //std::cout << "acaba" << '\n';
    //esto es codigo de swarm, basicamente para que a parte del flocking tengan todos un mismo destino
    ForceCenter();
    ChangeCenter();
}
void CFlock::ChangeCenter(){
    gg::Vector3f res;
    res.X=gg::genFloatRandom(-0.5,0.5);
    res.Y=gg::genFloatRandom(-0.5,0.5);
    pos+=res;

}
void CFlock::ForceCenter(){
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

}
void CFlock::addFlocked(CRigidBody* me){
    //CRigidBody* body = static_cast<CRigidBody*>(Manager->getComponent(gg::RIGID_BODY,me));
    Flocked.push_back(me);
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
