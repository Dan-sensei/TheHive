#ifndef ZSTATICMESH_H
#define ZSTATICMESH_H

#include <vector>
#include <cstdint>
#include "ZMaterial.hpp"
#include "ZMeshData.hpp"
#include "TNodo.hpp"
#include <glm/glm.hpp>
#include "TCamara.hpp"

class ZStaticMesh : public TEntidad {
    public:
        ZStaticMesh();
        ZStaticMesh(const ZStaticMesh &orig) = delete;
        ~ZStaticMesh();

        bool load(const std::string& Name);
        void assignMaterial(ZMaterial* material_);
        void FrustumCullingTest();
        void enableFrustumCulling(bool flag);

        virtual void beginDraw();
        virtual void Dro();
        virtual void JustRender();
        virtual void endDraw();

        void addLOD(std::string Name);

        static void setPlayerPtr(glm::vec3* _PlayerPosition);
        static void setMainCamera(TCamara* _camera);

    private:

        glm::mat4 localMVP;
        glm::mat4 localModelMatrix;

        static glm::vec3* PlayerPosition;
        static TCamara* camera;
        std::vector<ZMeshData*> MeshLODs;

        ZMaterial* zmat;
        GLuint MVP;
        GLuint M;

        GLuint MVP_Z;

        using TargetFunc = void(ZStaticMesh::*)();
        TargetFunc toDo;
};

#endif
