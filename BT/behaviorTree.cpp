// Primera generacion de BT
#include "behavior.hpp"

class BehaviorTree {
   protected:
      behavior* m_pRoot;
   public:
      void tick(); // "Delega" la funcion al root node
};