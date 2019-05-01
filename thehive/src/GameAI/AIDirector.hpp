#ifndef AIDIRECTOR
#define AIDIRECTOR

#include <chrono>
#include <Omicron/2D/Motor2D.hpp>
#include <vector>
#include <list>
#include <ComponentArch/ObjectManager.hpp>
#include <Singleton.hpp>
#include <Factory.hpp>

#include <ComponentArch/Components/CCamera.hpp>
#include <ComponentArch/Components/CRenderable_3D.hpp>
#include <ComponentArch/Components/CAIEnem.hpp>

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

        void invocar();
        void invocarrusher(AINode* nodo);
        void invocartank(AINode* nodo);
        void invocarswarm(AINode* nodo);



        void createWandering(AINode* nodo);
        void createHorda(AINode* nodo);
        void busquedaCerca();

        void changeNode(AINode* nodo);

        void comprobar();

        void removePos(AINode* nodo);

        AINode* createNode(glm::vec3 _pos,float _range);


        void clean();
        void init();

        void clipingEnemigos();
        void removeEnemy(CTransform* nodo);

    private:
        AINode* Njugador;
        CTransform* Pjugador;
        std::vector<AINode* > nodos;
        std::vector<CTransform*> enemigos;

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


        CCamera* camera;

};
//nodos
class AINode {
    public:
        AINode();
        AINode(glm::vec3,float _range);
        AINode(const AINode &orig);
        void addNode(AINode*);

        ~AINode();

        std::vector<AINode* > nodosProximos;

        glm::vec3 getPos();
        bool getonRange();
        void setonRange(bool);
        float getRange();
    private:
        //faces
        glm::vec3 pos;//ya no hace falta
        bool onRange;
        float range;//ya no hace falta

};
#endif
