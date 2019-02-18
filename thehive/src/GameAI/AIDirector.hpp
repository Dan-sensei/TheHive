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
class AINode;
class AIDirector {
    friend class Singleton<AIDirector>;
public:
    AIDirector (const AIDirector &orig);
    AIDirector (int _id,float _duracion,int _cooldown);
    AIDirector ();
    virtual ~AIDirector ();
    void update(float);
    void setActive(bool);
    void subida();
    void pico();
    void bajada();

    void invocacion(AINode*);
    void invocar();


    void createWandering(AINode* nodo);
    void createHorda(AINode* nodo);
    void busquedaCerca();

    void changeNode(AINode* nodo);

    void comprobar();

    void removePos(AINode* nodo);

    AINode* createNode(gg::Vector3f _pos,float _range);


    void clean();
    void init();

    void clipingEnemigos();
    void removeEnemy(CTransform* nodo);
private:
    AINode* Njugador;
    CTransform* Pjugador;
    std::vector<AINode* > nodos;
    std::list<CTransform*> enemigos;

    //std::chrono::high_resolution_clock::time_point nTimeStamp;
    ObjectManager* Manager;
    Factory* fac;
    float estres;//1-100
    bool activado;
    bool canWander;
    bool canHorde;
    int numEnemigos;
    //topes
    float TimeBusqueda;
    float TimeHorda;
    float TimePico;
    //acumuladores
    float AcumulatorBusqueda;
    float AcumulatorHorda;
    float AcumulatorPico;
};
class AINode {
public:
    AINode();
    AINode(gg::Vector3f,float _range);
    AINode(const AINode &orig);
    void addNode(AINode*);

    ~AINode();

    std::vector<AINode* > nodosProximos;

    gg::Vector3f getPos();
    bool getonRange();
    void setonRange(bool);
    float getRange();
private:
    gg::Vector3f pos;
    bool onRange;
    float range;

};
#endif
