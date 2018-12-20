#ifndef FACTORY_H
#define FACTORY_H

#include <ComponentArch/ObjectManager.hpp>
#include <GameEngine/GameEngine.hpp>
#include <Util.hpp>



template <typename T>
class Singleton;

class Factory{
    friend class Singleton<Factory>;

    public:
        uint16_t createHero(const gg::Vector3f &Position,bool);

        uint16_t createCollisionableStaticModel(const std::string &Path, const std::string &BulletPath, const std::string &Texture, const gg::Vector3f &Position);
        uint16_t createStaticModel(const std::string &Path, const std::string &Texture, const gg::Vector3f &Position, const gg::Vector3f &Rotation = gg::Vector3f());
        uint16_t createPathFindingActor(const gg::Vector3f &Position);

        void LoadNavmeshTestMap1();
    private:

        Factory();
        Factory(const Factory &orig) = delete;
        void operator=(const Factory &orig) = delete;

        ObjectManager* Manager;
        GameEngine* Engine;

};

#endif
