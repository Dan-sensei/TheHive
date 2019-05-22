#ifndef _EnumDataType_H
#define _EnumDataType_H

enum EnumDataType{
    kDat_Damage,            // Cantidad de danyo de un arma
    kDat_Matri,
    kDat_EntId,
    kDat_WeaponType,        // Un perro
    kDat_Action,            // Numero que dictamina el update que realizara dicho CRigidBody
    kDat_Done,              // 0-1 | false-true
    kDat_PickableItemId,    // Id de la entidad, que es un pickableItem
    kDat_LoadThatZone,      // Numero/ID de la zona a cargar o descargar
    kDat_total_img,          //total de imagenes en un pop up
    kDat_img1,              //img 1
    kDat_img2,              //img 2
    kDat_img3,              //img 3
    kDat_soundRoute
};

enum EnumActionType{
    Action_AbrirPuerta,
    Action_MoverObjeto
};
#endif
