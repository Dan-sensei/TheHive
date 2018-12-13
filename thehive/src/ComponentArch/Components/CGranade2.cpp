#include "CGranade2.hpp"

CGranade2::CGranade2()
: CGranade(30,0)
{}

CGranade2::~CGranade2() {}

void CGranade2::explosion(){
    TData mes;
    int dur = 3000;
    EventSystem->RegisterTriger(kTrig_Senyuelo,1,0,cTransform->getPosition(), radius, dur,false,mes);
}
