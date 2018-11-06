#ifndef Task_HPP
#define Task_HPP

#include "Node.hpp"
#include "status.hpp"



class Task {
public:
Task(Node& node);
virtual void onInitialize();             // Es llamado UNA VEZ e inmediatamente antes de la primera llamada del update
virtual Status update() ;              // Update del comportamiento. Llamado cada vez que el comportamiento es actualizado
virtual void onTerminate(Status);
 //Status update();
protected:
  Node* m_Node;

};

#endif /* end of include guard: SEQUENCE_HPP */
