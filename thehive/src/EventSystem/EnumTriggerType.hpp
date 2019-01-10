#ifndef _EnumTriggerType_H
#define _EnumTriggerType_H

enum EnumTriggerType{
    kTrig_none          =0<<0,  // 0
    kTrig_Explosion     =1<<0,  // 1
    kTrig_EnemyNear     =1<<1,  // 2
    kTrig_Gunfire       =1<<2,  // 4 -> para recoger armas
    kTrig_Shoot         =1<<3,  // 8
    kTrig_Touchable     =1<<4,  // 16
    kTrig_Senyuelo      =1<<5,  // 32
    kTrig_Aturd         =1<<6,  // 64
    kTrig_Pickable      =1<<7,  // 128
    kTrig_DeadAlien     =1<<8,  // 256
    kTrig_ExpansiveWave =1<<9,
    kTrig_ExpansiveForce =1<<10
};
#endif
