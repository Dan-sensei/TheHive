#include "CGranade0.hpp"


#include "ComponentArch/Message.hpp"

#include <EventSystem/TData.hpp>
#include "Factory.hpp"


CGranade0::CGranade0()
: CGranade(600),damage(6000)

{
}

CGranade0::~CGranade0() {

}

void CGranade0::explosion(){
    TData mes;
    mes.add(kDat_damage,damage);
    EventSystem->RegisterTriger(kTrig_Explosion,1,0,cTransform->getPosition(), radius, 50,false,mes);
}
