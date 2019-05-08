#ifndef CSTATICMODEL_H
#define CSTATICMODEL_H

#include <Singleton.hpp>
#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/Message.hpp>            // [OPCIONAL] Si necesitas recibir mensajes o inicializar variables punteros a otras componentes
#include <Omicron/Omicron.hpp>
#include <Omicron/ZMaterial.hpp>
#include <ComponentArch/ObjectManager.hpp>      // [OPCIONAL] Si necesitas acceder a algún método de ObjectManager

class CStaticModel : public IComponent {
    public:
        CStaticModel(StandardNode* FATHER, const std::string &pathToModel, ZMaterial* material, const glm::vec3 &Position, const glm::quat &Rotation);
        CStaticModel(ZNode* NODE, ZMaterial* material);
        CStaticModel(const CStaticModel &orig);
        virtual ~CStaticModel();

        void setVisibility(bool flag);
        void setPosition(const glm::vec3 &Position);
        void addLOD(std::string LOD);

    private:
        Omicron* Surreal;
        ZNode* _3DModel;

};

#endif
