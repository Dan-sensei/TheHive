#include "Parallel.hpp"

Parallel::Parallel(){}
Parallel::~Parallel(){}

void Parallel::onInitialize() {
    ////std::cout << "init paraller" << '\n';
    auto it=m_Children.begin();
    while(it!=m_Children.end()){
        Behavior* b=*it;
        b->tick();
        it++;
    }
}//m_CurrentChild=m_Children.begin();

void Parallel::onTerminate(Status state){
    ////std::cout << "finish paraller" << '\n';
    auto it=m_Children.begin();
    while(it!=m_Children.end()){
        Behavior* b=*it;
        b->abort();
        it++;
    }
}

Status Parallel::update() {
    size_t iSuccessCount = 0,iFailureCount=0;
    auto it=m_Children.begin();
    ////std::cout << "parallel" << '\n';
    while(it!=m_Children.end()){
    //    //std::cout << "hijo" << '\n';
      Behavior* b=*it;
      ////std::cout << "estatus" <<b->getStatus()<< '\n';
      if(!b->isTerminate()) b->tick();
      if(b->getStatus()==BH_SUCCESS){
        iSuccessCount++;
        if(m_eSuccesPolicy==RequireOne)return BH_SUCCESS;
      }
      if(b->getStatus()==BH_FAILURE){
        iFailureCount++;
        if(m_eFailurePolicy==RequireOne)return BH_FAILURE;
      }
      it++;
    }

    if(m_eFailurePolicy==RequireAll && iFailureCount == m_Children.size()) return BH_FAILURE;
    if(m_eSuccesPolicy==RequireAll && iSuccessCount == m_Children.size()) return BH_SUCCESS;

    return BH_RUNNING;
}

Parallel::Parallel(Policy succes,Policy failure){
   m_eSuccesPolicy=succes;
   m_eFailurePolicy=failure;
}
