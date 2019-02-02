#ifndef _CFLOCK_H
#define _CFLOCK_H

#include <ComponentArch/IComponent.hpp>         // [OBLIGATORIO]
#include <list>
#include <ComponentArch/ObjectManager.hpp>      // [OPCIONAL] Si necesitas acceder a algún método de ObjectManager
#include <Util.hpp>
//#include <ComponentArch/Components/CRigidBody.hpp>      // [OPCIONAL] Si necesitas acceder a algún método de ObjectManager
#include "CRigidBody.hpp"


class CFlock : public IComponent {
    public:
        CFlock();
        CFlock(gg::Vector3f _pos);
        CFlock(const CFlock &orig) = delete;
        virtual ~CFlock();

        // Functions of IComponent
        virtual void Init();
        virtual void FixedUpdate();

        //funciones propias
        void addFlocked(CRigidBody* me);
        void debugtotal();
        void ForceCenter();
        void ChangeCenter();
        void FastSeparation();
        void FastAlignementAndCohesion();


        //variables propias
        std::list  <CRigidBody*>  Flocked;

    private:
        
        float mindist;//minima distancia para aplica separacion
        float fuerzasep;//fuerza separacion
        float fuerzacoh;//fuerza cohesion
        //media de posicion y velocidad, (sirven para hacer los calculos mas rapidos)
        gg::Vector3f mediapos;
        gg::Vector3f mediavel;
        //Esto el del swarm. posicion donde se dirigen
        gg::Vector3f pos;

        ObjectManager* Manager;

};

#endif
