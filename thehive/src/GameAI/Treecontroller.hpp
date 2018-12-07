#ifndef TREECONTROLLER
#define TREECONTROLLER

#include "EventSystem/Blackboard.hpp"
#include <BT/BehaviorTree.hpp>
#include "ComponentArch/Components/CAIEnem.hpp"

#include <vector>
class CAIEnem;
class Treecontroller {
private:
    /* data */
    Blackboard* data;

    using Behaviors = std::vector<Behavior*>;
    Behaviors m_Children;

    BehaviorTree* BT;
CAIEnem* yo;
public:
    Treecontroller (Blackboard* _data,int tipo,CAIEnem* ai);
    Treecontroller ();
    //void iniciar (Blackboard* _data);
    virtual ~Treecontroller ();
    void arbolsoldado();
    void arboltracker();
    void arbolrusher();
    void arboltank();


    void reset();
    void update();

};
#endif
