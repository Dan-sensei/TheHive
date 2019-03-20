#ifndef BEHAVIORTREE_HPP
#define BEHAVIORTREE_HPP

#include "Behavior.hpp"
//#include <iostream>

class BehaviorTree {
    protected:
        Behavior* b_Root;
    public:
        BehaviorTree();
        BehaviorTree(Behavior* behavior_Root);
        ~BehaviorTree();
        void tick();
};
#endif
