#ifndef _CCUSTOMSCENENODE_H
#define _CCUSTOMSCENENODE_H

#include <irrlicht/irrlicht.h>

//  ---
//  TESTING! Class for making custom nodes on Irrlicht. Just ignore it :D
//

class CCustomSceneNode : public irr::scene::ISceneNode{
public:
    CCustomSceneNode(irr::scene::ISceneNode* parent, irr::scene::ISceneManager* mgr, irr::s32 id);
    virtual void OnRegisterSceneNode();
    virtual void render();

    virtual const irr::core::aabbox3d<irr::f32>& getBoundingBox() const;
    virtual irr::u32 getMaterialCount() const;
    virtual irr::video::SMaterial& getMaterial(irr::u32 i);
private:
    irr::core::aabbox3d<irr::f32> Box;
    irr::video::S3DVertex Vertices[4];
    irr::video::SMaterial Material;
};

#endif
