#ifndef TREECONTROLLER
#define TREECONTROLLER

#include <vector>
#include <map>
#include <Util.hpp>

#include <BT/BehaviorTree.hpp>
#include <BT/Action.hpp>

#include "EventSystem/Blackboard.hpp"
#include "ComponentArch/Components/CAIEnem.hpp"
//#include "BT/Hojas.hpp"


class CAIEnem;
class Action;
class Parallel;
class Sequence;
class Selector;
class Inverso;
class RandomSelector;
//enum Hojas;
class Treecontroller {
    public:

        Treecontroller (Blackboard*,gg::EEnemyType,CAIEnem*);
        Treecontroller ();
        virtual ~Treecontroller();

        void reset();
        int taskactual();
        void update();

        Action* addAction(Hojas ac);
        void arbolsoldado();
        void arboltracker();
        void arbolrusher();
        void arboltank();
        void arbolswarm();

    private:
        Parallel* createParallel(Behavior* condiciones);
        Inverso* createInverso(Behavior* condiciones);
        Sequence* createSequence();
        Selector* createSelector();
        RandomSelector* createRandomSelector();
        /* data */
        CAIEnem* yo;
        BehaviorTree* BT;

        using Behaviors = std::vector<Behavior*>;
        Behaviors m_Children;

        Blackboard* data;

};
#endif
