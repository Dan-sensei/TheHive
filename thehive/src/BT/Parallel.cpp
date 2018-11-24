#include "Parallel.hpp"

Parallel::Parallel(){}
Parallel::~Parallel(){}

void Parallel::onInitialize() {}//m_CurrentChild=m_Children.begin();

void Parallel::onTerminate(Status state){
  //std::cout << "Parallel onTerminate" << state << '\n';
  for(auto it:m_Children){
    Behavior b=*it;
    if(!b.isTerminate()) b.abort();
  }
}

Status Parallel::update() {
    size_t iSuccessCount = 0,iFailureCount=0;
    for(auto it:m_Children){
      Behavior b=*it;
      if(!b.isTerminate()) b.tick();
      if(b.getStatus()==BH_SUCCESS){
        iSuccessCount++;
        if(m_eSuccesPolicy==RequireOne)return BH_SUCCESS;
      }
      if(b.getStatus()==BH_FAILURE){
        iFailureCount++;
        if(m_eFailurePolicy==RequireOne)return BH_FAILURE;
      }
    }

    if(m_eFailurePolicy==RequireAll && iFailureCount == m_Children.size()) return BH_FAILURE;
    if(m_eSuccesPolicy==RequireAll && iSuccessCount == m_Children.size()) return BH_SUCCESS;

    return BH_RUNNING;
}

Parallel::Parallel(Policy succes,Policy failure){
   m_eSuccesPolicy=succes;
   m_eFailurePolicy=failure;
}
