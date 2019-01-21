#ifndef TREECONTROLLER
#define TREECONTROLLER

#include <vector>
#include <map>
#include <Util.hpp>

#include <BT/BehaviorTree.hpp>

#include "EventSystem/Blackboard.hpp"
#include "ComponentArch/Components/CAIEnem.hpp"


class CAIEnem;
class Treecontroller {
    public:
        Treecontroller (Blackboard*,gg::EEnemyType,CAIEnem*);
        Treecontroller ();
        virtual ~Treecontroller();

        void reset();
        int taskactual();
        void update();

        void arbolsoldado();
        void arboltracker();
        void arbolrusher();
        void arboltank();

    private:
        /* data */
        CAIEnem* yo;
        BehaviorTree* BT;

        using Behaviors = std::vector<Behavior*>;
        Behaviors m_Children;

        Blackboard* data;

};
#endif
