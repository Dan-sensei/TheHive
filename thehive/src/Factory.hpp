#ifndef FACTORY_H
#define FACTORY_H

#include <ComponentArch/ObjectManager.hpp>
#include <GameEngine/GameEngine.hpp>
#include <Util.hpp>

#include <ComponentArch/Components/ComponentHeaders.hpp>

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

        void ComponentInitializer();
        
        ObjectManager* Manager;
        GameEngine* Engine;

};

#endif
