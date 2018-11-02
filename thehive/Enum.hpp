#ifndef _ENUM_H
#define _ENUM_H

enum EComponentType{
    TRANSFORM = 0,
    //COLLIDER,
    //RENDERABLE,
    //HEALTH,
    //RESPECT,
    NUM_COMPONENTS
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

#endif
