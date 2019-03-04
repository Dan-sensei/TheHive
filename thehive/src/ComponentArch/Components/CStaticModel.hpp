#ifndef CSTATICMODEL_H
#define CSTATICMODEL_H

#include <Singleton.hpp>
#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/Message.hpp>            // [OPCIONAL] Si necesitas recibir mensajes o inicializar variables punteros a otras componentes
#include <SurrealEngine/TMotorTAG.hpp>
#include <SurrealEngine/ZMaterial.hpp>
#include <ComponentArch/ObjectManager.hpp>      // [OPCIONAL] Si necesitas acceder a algún método de ObjectManager

class CStaticModel : public IComponent {
    public:
        CStaticModel(const std::string &pathToModel, ZMaterial* material, const glm::vec3 &Position, const glm::vec3 &Rotation);
        CStaticModel(const CStaticModel &orig);
        virtual ~CStaticModel();

    private:

};

#endif
