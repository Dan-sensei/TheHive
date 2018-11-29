#ifndef _ENUM_H
#define _ENUM_H

namespace gg{

    enum EComponentType{
        TRANSFORM = 0,
        PLAYERCONTROLLER,
        RENDERABLE_3D,
        CAMERA,
        RIGID_BODY,
        AGENT,
        GRANADE,
        GUN,
        PATHFINDING,
        AIENEM,
        CLOCK,
        //HEALTH,
        //RESPECT,
        //DANINOSABEPROGRAMAR
        NUM_COMPONENTS
    };
    enum EEnemyType{
        SOLDIER,
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
