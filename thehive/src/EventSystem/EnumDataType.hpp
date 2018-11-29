#ifndef _EnumDataType_H
#define _EnumDataType_H

enum EnumDataType{
    kDat_damage,
    kDat_Matri,
    kDat_EntId,
    kDat_WeaponType,
    kDat_Action,
    kDat_Done            // 0-1 | false-true
};

enum EnumActionType{
    Action_AbrirPuerta,
    Action_MoverObjeto
};
#endif
