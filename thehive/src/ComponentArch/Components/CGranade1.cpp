#include "CGranade1.hpp"

#define VEL_FACTOR      200.f

CGranade1::CGranade1()
: CGranade(50,300),damage(1000)//, tipo(_tipo)
{
}

CGranade1::~CGranade1() {

}
void CGranade1::explosion(){
    gg::Vector3f currentPosition = cTransform->getPosition();

    TData mes;
    mes.add(kDat_Damage,damage);
    EventSystem->RegisterTriger(kTrig_Explosion,1,0,currentPosition, radius, 50,false,mes);

    float alejamiento=5;
    float ymas=10;
    float decrecimiento=0.75;
    gg::Vector3f vel(0,ymas,1);
    vel = gg::Normalice(vel);
    vel*= VEL_FACTOR*decrecimiento;

    Singleton<Factory>::Instance()->createHolyBomb(
        gg::Vector3f(currentPosition.X,currentPosition.Y+alejamiento,currentPosition.Z+alejamiento),
        vel
    );

    //segunda granada Z-
    vel=gg::Vector3f(0,ymas,-1);
    vel = gg::Normalice(vel);
    vel*= VEL_FACTOR*decrecimiento;
    Singleton<Factory>::Instance()->createHolyBomb(
        gg::Vector3f(currentPosition.X,currentPosition.Y+alejamiento,currentPosition.Z-alejamiento),
        vel
    );

    //tercera granada X+
    vel=gg::Vector3f(1,ymas,0);
    vel = gg::Normalice(vel);
    vel*= VEL_FACTOR*decrecimiento;
    Singleton<Factory>::Instance()->createHolyBomb(
        gg::Vector3f(currentPosition.X+alejamiento,currentPosition.Y+alejamiento,currentPosition.Z),
        vel
    );

    //cuarta granada X-
    vel=gg::Vector3f(-1,ymas,0);
    vel = gg::Normalice(vel);
    vel*= VEL_FACTOR*decrecimiento;
    Singleton<Factory>::Instance()->createHolyBomb(
        gg::Vector3f(currentPosition.X-alejamiento,currentPosition.Y+alejamiento,currentPosition.Z),
        vel
    );


}
