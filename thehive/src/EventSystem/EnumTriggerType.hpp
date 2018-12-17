#ifndef _EnumTriggerType_H
#define _EnumTriggerType_H

enum EnumTriggerType{
    kTrig_none      =0<<0,  // 0
    kTrig_Explosion =1<<0,  // 1
    kTrig_Gunfire   =1<<1,  // 4 -> para recoger armas
    kTrig_Shoot     =1<<2,  // 8
    kTrig_Touchable =1<<3,  // 16
    kTrig_Senyuelo  =1<<4,  // 32
    kTrig_Aturd     =1<<5,  // 64
    kTrig_Pickable  =1<<6   // 128

};
#endif
