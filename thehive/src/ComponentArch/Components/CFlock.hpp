#ifndef _CFLOCK_H
#define _CFLOCK_H
#define GLM_ENABLE_EXPERIMENTAL

#include <ComponentArch/IComponent.hpp>         // [OBLIGATORIO]
#include <list>
#include <ComponentArch/ObjectManager.hpp>      // [OPCIONAL] Si necesitas acceder a algún método de ObjectManager
#include <Util.hpp>
#include "CRigidBody.hpp"


class CFlock : public IComponent {
    public:
        CFlock();
        CFlock(bool lider,uint16_t id=-1);
        CFlock(const CFlock &orig) = delete;
        virtual ~CFlock();

        // Functions of IComponent
        virtual void Init();
        virtual void FixedUpdate();

        //funciones propias
        //funcionamiento a lista cerrada
        void debugtotal();
        void FastSeparation();
        void FastAlignementAndCohesion();

        //funciones para modificar lista
        void addNewFlocked(uint16_t me);
        void addFlocked(uint16_t me);
        void setLeader(int);
        void setIAmLeader(bool id);
        void removerFlocked(int id);
        void setNewLeader();
        bool getLeader();
        int getLeaderID();


        std::list  <CRigidBody*> getFlocked();
        void copyFlocked(int id);
        void Muerte();
        //variables propias
        std::list  <CRigidBody*> Flocked;

    private:
        int leader_id;
        bool leader;//si es el lider
        float mindist;//minima distancia para aplica separacion
        float fuerzasep;//fuerza separacion
        float fuerzacoh;//fuerza cohesion
        float fuerzaalign;//fuerza cohesion
        //media de posicion y velocidad, (sirven para hacer los calculos mas rapidos)
        glm::vec3 mediapos;
        glm::vec3 mediavel;

        ObjectManager* Manager;

};

#endif
