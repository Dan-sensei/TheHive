#ifndef AIDIRECTOR
#define AIDIRECTOR

#include <chrono>
#include <GameEngine/ScreenConsole.hpp>
#include <vector>
#include <list>
//#include <string>
//class Singleton;

class ObjectManager;
class Factory;
class CTransform;
class AIDirector {
    friend class Singleton<AIDirector>;
public:
    AIDirector (const AIDirector &orig);
    AIDirector (int _id,float _duracion,int _cooldown);
    AIDirector ();
    virtual ~AIDirector ();
    void update();
    void setActive(bool);
    void subida();
    void pico();
    void bajada();

    void createWandering(gg::Vector3f posicion,float rango);
    void createHorda(gg::Vector3f posicion,float rango);


    void clean();
    void init();


protected:
    std::vector<gg::Vector3f > nodos;
    std::list<CTransform*> enemigos;

    //std::chrono::high_resolution_clock::time_point nTimeStamp;
    ObjectManager* Manager;
    Factory* fac;
    float estres;
    bool activado;
    int numEnemigos;
};
#endif
