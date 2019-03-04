#include "CGranade1.hpp"

#define VEL_FACTOR      200.f

CGranade1::CGranade1()
: CGranade(30,500),damage(1000)//, tipo(_tipo)
{
}

CGranade1::~CGranade1() {

}
void CGranade1::explosion(){
    int dirs[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

    glm::vec3 currentPosition = cTransform->getPosition();

    float   alejamiento=3,
            ymas=10,
            decrecimiento=0.75;

    TData mes;
    mes.add(kDat_Damage,damage);
    EventSystem->RegisterTriger(kTrig_Explosion,1,0,currentPosition, radius, 50,false,mes);
    for(int i=0 ; i<4 ; i++){
        glm::vec3 vel(dirs[i][0],ymas,dirs[i][1]);
        vel = glm::normalize(vel);
        vel*= VEL_FACTOR*decrecimiento;

        factory->createHolyBomb(glm::vec3(currentPosition.x+dirs[i][0]*alejamiento,currentPosition.y+alejamiento,currentPosition.z+dirs[i][1]*alejamiento),vel);
    }


    // //segunda granada Z-
    // vel=glm::vec3(0,ymas,-1);
    // vel = glm::normalize(vel);
    // vel*= VEL_FACTOR*decrecimiento;
    // Singleton<Factory>::Instance()->createHolyBomb(
    //     glm::vec3(currentPosition.x,currentPosition.y+alejamiento,currentPosition.z-alejamiento),
    //     vel
    // );
    //
    // //tercera granada X+
    // vel=glm::vec3(1,ymas,0);
    // vel = glm::normalize(vel);
    // vel*= VEL_FACTOR*decrecimiento;
    // Singleton<Factory>::Instance()->createHolyBomb(
    //     glm::vec3(currentPosition.x+alejamiento,currentPosition.y+alejamiento,currentPosition.z),
    //     vel
    // );
    //
    // //cuarta granada X-
    // vel=glm::vec3(-1,ymas,0);
    // vel = glm::normalize(vel);
    // vel*= VEL_FACTOR*decrecimiento;
    // Singleton<Factory>::Instance()->createHolyBomb(
    //     glm::vec3(currentPosition.x-alejamiento,currentPosition.y+alejamiento,currentPosition.z),
    //     vel
    // );

}
