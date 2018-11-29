#ifndef _EnumTriggerType_H
#define _EnumTriggerType_H

enum EnumTriggerType{
    kTrig_none      =0<<0,
    kTrig_Explosion =1<<0,
    kTrig_EnemyNear =1<<1,
    kTrig_Gunfire   =1<<2,
    kTrig_Shoot     =1<<3,
    kTrig_Touchable =1<<4
};
#endif
