// Primera generacion de BT
#include "behaviorTree.hpp"

void BehaviorTree::tick(){
  std::cout << "BT tick" << '\n';

m_pRoot->tick();
}

BehaviorTree::BehaviorTree(behavior* _m_pRoot){
  m_pRoot=_m_pRoot;
}
BehaviorTree::~BehaviorTree(){

}
BehaviorTree::BehaviorTree(){

}


//mejora en la memoria
/*
     BehaviorTree::BehaviorTree(){
     m_pBuffer=new uint8_t[k_MaxBehaviourTreeMemory];
     m_iOffset=0;
   }
     BehaviorTree::~BehaviorTree(){
       delete [] m_pBuffer;
     }
      void BehaviorTree::tick(){

      } // "Delega" la funcion al root node
      template<typename T>
      T& BehaviorTree::allocate(){
        T* node = new((void*)((uintptr_t)m_pBuffer+m_iOffset)) T;
        m_iOffset +=sizeof(T);
        return *node;
      }
*/
