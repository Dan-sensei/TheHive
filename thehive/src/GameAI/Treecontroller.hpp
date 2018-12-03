#ifndef TREECONTROLLER
#define TREECONTROLLER

#include "EventSystem/Blackboard.hpp"
#include <BT/BehaviorTree.hpp>
#include <vector>

class Treecontroller {
private:
    /* data */
    Blackboard* data;

    using Behaviors = std::vector<Behavior*>;
    Behaviors m_Children;

    BehaviorTree* BT;


public:
    Treecontroller (Blackboard* _data);
    Treecontroller ();
    //void iniciar (Blackboard* _data);
    virtual ~Treecontroller ();
    void arbolsoldado();
    void reset();
    void update();

};
#endif
