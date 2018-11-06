// Primera generacion de BT
#ifndef BehaviorTree_HPP
#define BehaviorTree_HPP
#include "behavior.hpp"
#include <iostream>

//#include <cstddef>
//#include <stdint.h>
//const int k_MaxBehaviourTreeMemory=7;


class BehaviorTree {

   public:
     BehaviorTree();
     BehaviorTree(behavior* _m_pRoot);
     ~BehaviorTree();
      void tick();
    protected:
      behavior* m_pRoot;

};

/*


class BehaviorTree {

   public:
     BehaviorTree();
     ~BehaviorTree();
      void tick(); // "Delega" la funcion al root node
      template<typename T>
      T& allocate();
    protected:
      uint8_t* m_pBuffer;
      size_t m_iOffset;

};
*/
#endif /* end of include guard: SEQUENCE_HPP */
