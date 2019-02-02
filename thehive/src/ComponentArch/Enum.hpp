#ifndef _ENUM_H
#define _ENUM_H

namespace gg{

    enum EComponentType{
        PLAYERCONTROLLER,
        RIGID_BODY,
        RENDERABLE_3D,
        GRANADE,
        GUN,
        NAVMESHAGENT,
        HAB,
        AIENEM,
        CLOCK,
        VIDA,
        FLOCK,

        CAMERA,
        AGENT,
        TRANSFORM,
        //HEALTH,
        //RESPECT,
        //PABLONDEMADERANOSABEPROGRAMAR
        NUM_COMPONENTS
    };

    // ORDENADOS DE MAYOR A MENOR VELOCIDAD DE MOVIMIENTO!!
    enum EEnemyType{
        RUSHER,
        SOLDIER,
        TRACKER,
        TANK,
        NUM_ENEMY
    };

    enum EMessageStatus{
        ST_TRUE,
        ST_FALSE,
        ST_IGNORED,
        ST_ERROR
    };

//enum MemoryForComponentType{
//    TRANSFORM   = 128,
//    COLLIDER    = 128,
//    RENDERABLE  = 128,
//    HEALTH      = 128,
//    RESPECT     = 128
//}
}

#endif
