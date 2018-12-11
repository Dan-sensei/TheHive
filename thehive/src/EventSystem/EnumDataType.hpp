#ifndef _EnumDataType_H
#define _EnumDataType_H

enum EnumDataType{
    kDat_Damage,            // Cantidad de danyo de un arma
    kDat_Matri,
    kDat_EntId,
    kDat_WeaponType,        // Un perro
    kDat_Action,            // Numero que dictamina el update que realizara dicho CRigidBody
    kDat_Done,              // 0-1 | false-true
    kDat_PickableItemId     // Id de la entidad, que es un pickableItem
};

enum EnumActionType{
    Action_AbrirPuerta,
    Action_MoverObjeto
};
#endif
