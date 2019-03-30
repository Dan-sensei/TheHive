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
        CStaticModel(const std::string &pathToModel, ZMaterial* material, const glm::vec3 &Position, const glm::vec3 &Rotation, int8_t map_zone = 0,const std::string& BoundingBoxPath = "");
        CStaticModel(const CStaticModel &orig);
        virtual ~CStaticModel();

        void setVisibility(bool flag);
        void setPosition(const glm::vec3 &Position);
        void addLOD(std::string LOD);

    private:
        Omicron* Surreal;
        TNodo* _3DModel;

};

#endif
