#ifndef FACTORY_H
#define FACTORY_H

#include <ComponentArch/ObjectManager.hpp>
#include <GameEngine/GameEngine.hpp>
#include <Util.hpp>

#include "ComponentArch/Components/CTransform.hpp"
#include "ComponentArch/Components/CPlayerController.hpp"
#include "ComponentArch/Components/CRenderable_3D.hpp"
#include "ComponentArch/Components/CCamera.hpp"
#include "ComponentArch/Components/CAgent.hpp"
#include "ComponentArch/Components/CRigidBody.hpp"
#include "ComponentArch/Components/CGranade.hpp"
#include "ComponentArch/Components/CGun.hpp"
#include "ComponentArch/Components/CPathfinding.hpp"
#include "ComponentArch/Components/CAIEnem.hpp"

template <typename T>
class Singleton;

class Factory{
    friend class Singleton<Factory>;

    public:
        void createHero(const gg::Vector3f &Position);
        void createEnemy(const gg::Vector3f &Position);
        void createCollisionableStaticModel(const std::string &Path, const std::string &BulletPath, const std::string &Texture, const gg::Vector3f &Position);
        void createStaticModel(const std::string &Path, const std::string &Texture, const gg::Vector3f &Position, const gg::Vector3f &Rotation = gg::Vector3f());
        void createPathFindingActor(const gg::Vector3f &Position);
        void createHolyBomb(float _damage,float _radius,float _tipo, const gg::Vector3f &Position, const gg::Vector3f &Impulse);

    private:

        Factory();
        Factory(const Factory &orig) = delete;
        void operator=(const Factory &orig) = delete;

        ObjectManager* Manager;
        GameEngine* Engine;

};

#endif