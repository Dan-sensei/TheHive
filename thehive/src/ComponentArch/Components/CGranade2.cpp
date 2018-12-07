#include "CGranade2.hpp"


#include "ComponentArch/Message.hpp"

#include <EventSystem/TData.hpp>
#include "Factory.hpp"


CGranade2::CGranade2()
: CGranade(600)
{
}

CGranade2::~CGranade2() {

}
void CGranade2::explosion(){
    TData mes;
    EventSystem->RegisterTriger(kTrig_Senyuelo,1,0,cTransform->getPosition(), radius, 10000,false,mes);
}
