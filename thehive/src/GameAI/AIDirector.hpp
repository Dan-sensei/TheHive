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
#include "NavmeshStructs.hpp"

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
        void invocarrusher(int nodo);
        void invocartank(int nodo);
        void invocarswarm(int nodo);

         glm::vec3 getposzona(int);
         int checkzone(glm::vec3 pos);

        void createWandering(int nodo);
        void createHorda(int nodo);
        void busquedaCerca();

        void changeNode(int nodo);

        void comprobar();

        void removePos(int nodo);

        //AINode* createNode(glm::vec3 _pos,float _range);


        void clean();
        void init();


        void removeEnemy(CTransform* nodo);

        void DrawZones();

    private:
        int zona_actual;
        //glm::vec3 ;
        //std::vector<AINode* > nodos;
        std::vector<CTransform*> enemigos;

        std::vector<SimpleFace> ZONAS[7];



        //std::chrono::high_resolution_clock::time_point nTimeStamp;
        //AINode* Njugador;
        CTransform* Pjugador;
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
/*
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
        glm::vec3 pos;
        bool onRange;
        float range;

};*/
#endif
