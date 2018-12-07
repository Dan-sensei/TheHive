#ifndef FACTORY_H
#define FACTORY_H

#include <ComponentArch/ObjectManager.hpp>
#include <GameEngine/GameEngine.hpp>
#include <EventSystem/CTriggerSystem.hpp>
#include <Util.hpp>

#include <ComponentArch/Components/ComponentHeaders.hpp>

#include <EventSystem/Blackboard.hpp>
#include <EventSystem/BRbData.hpp>
#include <EventSystem/BFloat.hpp>

template <typename T>
class Singleton;

class Factory{
    friend class Singleton<Factory>;

    public:
        uint16_t createHero(const gg::Vector3f &Position,bool);
        uint16_t createEnemy(const gg::Vector3f &Position);
        uint16_t createCollisionableStaticModel(const std::string &Path, const std::string &BulletPath, const std::string &Texture, const gg::Vector3f &Position);
        uint16_t createCollisionableDynamicModel(const std::string &Path, const std::string &BulletPath, const std::string &Texture, const gg::Vector3f &Position);
        uint16_t createStaticModel(const std::string &Path, const std::string &Texture, const gg::Vector3f &Position, const gg::Vector3f &Rotation = gg::Vector3f());
        uint16_t createPathFindingActor(const gg::Vector3f &Position);
        uint16_t createHolyBomb(float _damage,float _radius,float _tipo, const gg::Vector3f &Position, const gg::Vector3f &Impulse);
        uint16_t createCollectableWeapon(const gg::Vector3f&, int);
        uint16_t createPickableItem(const gg::Vector3f&);
        uint16_t createTouchableObject(const gg::Vector3f&, const uint16_t&, const gg::Vector3f&, const float&, uint16_t=0);
    private:

        Factory();
        Factory(const Factory &orig) = delete;
        void operator=(const Factory &orig) = delete;

        void ComponentInitializer();

        ObjectManager* Manager;
        GameEngine* Engine;

};

#endif
