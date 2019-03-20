//#include <iostream>
#include "UntilFail.hpp"

Status UntilFail::update(){
      ////std::cout << "estoy aqui :D" << '\n';

     Status s= m_pChild->tick();
     ////std::cout << "estatus " <<s<< '\n';

     if(s==BH_FAILURE){
      return BH_SUCCESS;
    }
    else{
        return BH_RUNNING;
    }
//  return BH_INVALID;
}


UntilFail::UntilFail(Behavior* _m_pChild):Decorator(_m_pChild){}
UntilFail::UntilFail(){}
UntilFail::~UntilFail(){}
void UntilFail::onTerminate(Status state){
}
