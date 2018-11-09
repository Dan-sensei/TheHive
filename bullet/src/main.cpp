/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2003-2007 Erwin Coumans  http://continuousphysics.com/Bullet/

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it freely,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

///-----includes_start-----
#include <stdio.h>

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>

#include "ggDynWorld.hpp"
#include "ggRigidBody.hpp"
#include "Singleton.hpp"

/// This is a Hello World program for running a basic Bullet physics simulation

int main(int argc, char** argv){
    ggDynWorld* world = Singleton<ggDynWorld>::Instance();

    // Plano que esta en P(0,0,0), con tamanyo S(1,5,1), masa=0 (OBJETO ESTATICO) e inercia I(0,0,0)
    ggRigidBody* plano = new ggRigidBody(0,0,0, 1,5,1, 0);

    // Cubo de lado 1, masa 1 e inercia 0
    ggRigidBody* cubo1 = new ggRigidBody(0,10,0);

    // SIMULACION
	for (int i = 0; i < 200; i++){
		world->stepSimulation(1.f / 60.f, 10);
        world->printObjects(1);
	}

    world->clean();
}
