#include "CCustomSceneNode.hpp"


CCustomSceneNode::CCustomSceneNode(irr::scene::ISceneNode* parent, irr::scene::ISceneManager* mgr, irr::s32 id)
: irr::scene::ISceneNode(parent, mgr, id)
{
    Material.Wireframe = false;
    Material.Lighting = false;

    Vertices[0] = irr::video::S3DVertex(0,0,10, 1,1,0,       irr::video::SColor(255,0,255,255), 0, 1);
    Vertices[1] = irr::video::S3DVertex(10,0,-10, 1,0,0,     irr::video::SColor(255,255,0,255), 1, 1);
    Vertices[2] = irr::video::S3DVertex(0,20,0, 0,1,1,       irr::video::SColor(255,255,255,0), 1, 0);
    Vertices[3] = irr::video::S3DVertex(-10,0,-10, 0,0,1,    irr::video::SColor(255,0,255,0), 0, 0);

    Box.reset(Vertices[0].Pos);
    for (irr::s32 i=1; i<4; ++i)
        Box.addInternalPoint(Vertices[i].Pos);
}

void CCustomSceneNode::OnRegisterSceneNode() {
    if (IsVisible)
        SceneManager->registerNodeForRendering(this);

    ISceneNode::OnRegisterSceneNode();
}


void CCustomSceneNode::render() {
    irr::u16 indices[] = {   0,2,3, 2,1,3, 1,0,3, 2,0,1  };
    irr::video::IVideoDriver* driver = SceneManager->getVideoDriver();

    driver->setMaterial(Material);
    driver->setTransform(irr::video::ETS_WORLD, AbsoluteTransformation);
    driver->drawVertexPrimitiveList(&Vertices[0], 4, &indices[0], 4, irr::video::EVT_STANDARD, irr::scene::EPT_TRIANGLES, irr::video::EIT_16BIT);
}

const irr::core::aabbox3d<irr::f32>& CCustomSceneNode::getBoundingBox() const{
    return Box;
}

irr::u32 CCustomSceneNode::getMaterialCount() const{
    return 1;
}

irr::video::SMaterial& CCustomSceneNode::getMaterial(irr::u32 i) {
    return Material;
}
