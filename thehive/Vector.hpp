#ifndef _Vector_H
#define _Vector_H

#include <map>
#include <iostream>
#include <math.h>
//#include <cstdlib>
//#include <iomanip>
#include <glm/glm.hpp>
//#include <time.h>
#include <sys/time.h>
#include <irrlicht/irrList.h>


struct Vector
{
  //glm::vec3 V3;
  float x;
  float y;
  float z;
  Vector();
  Vector(float _x,float _y, float _z);
  //glm::vec3 aVector(3);
};
static float DIST(Vector v1,Vector v2){
  return sqrt(((v1.x-v2.x)*(v1.x-v2.x)+(v1.y-v2.y)*(v1.y-v2.y)+(v1.z-v2.z)*(v1.z-v2.z)));
  //return 1;
}
//static void removeAgent(Iterator agente);

#endif
