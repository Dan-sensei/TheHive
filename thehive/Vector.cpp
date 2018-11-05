//#include <iostream>
//mio
//#include <cstdlib>
//#include <stdio.h>
//#include <stdlib.h>
//#include <termios.h>
//#include <term.h>
//#include <curses.h>
//#include <unistd.h>
//#include <vector>
#include "Agent.hpp"
#include "Vector.hpp"
#include "Time.hpp"
//static float DIST(Vector v1,Vector v2){
//  return sqrt(((v1.x-v2.x)*(v1.x-v2.x)+(v1.y-v2.y)*(v1.y-v2.y)+(v1.z-v2.z)*(v1.z-v2.z)));
//  //return 1;
//}

Vector::Vector(){
  x=0;
  y=0;
  z=0;


}
Vector::Vector(float _x,float _y, float _z){
  x=_x;
  y=_y;
  z=_z;


}
