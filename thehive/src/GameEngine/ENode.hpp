#ifndef ENODE_H
#define ENODE_H

#include <string>
#include <iostream>
#include <irrlicht/irrlicht.h>
// #include <irrlicht/ISceneNode.h>

class ENode {
public:
    ENode(std::string m,std::string t);
    ~ENode();

    void setMPath(std::string path)  {mPath=path;}
    void setTPath(std::string path)  {tPath=path;}

    std::string getMPath() {return mPath;}
    std::string getTPath() {return tPath;}

    void setAutomaticCulling(int);
protected:
    irr::scene::ISceneNode* getSceneNode() {return node;}
    irr::scene::IAnimatedMesh* getAnimatedMesh() {return mesh;}

    void setSceneNode(irr::scene::ISceneNode* _n) {node=_n;}
    void setAnimatedMesh(irr::scene::IAnimatedMesh* _m) {mesh=_m;}

private:
    irr::scene::IAnimatedMesh* mesh;
    irr::scene::ISceneNode* node;
    std::string mPath, tPath;

    friend class GameEngine;
};

#endif
