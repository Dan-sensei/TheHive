#ifndef _CRENDERABLE_3D_H
#define _CRENDERABLE_3D_H

#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/Message.hpp>
#include <Omicron/ZStaticMesh.hpp>
#include <Omicron/ZMaterial.hpp>
#include <map>
//#include <iostream>
#include <Singleton.hpp>
#include <Omicron/Omicron.hpp>


class CTransform;

class CRenderable_3D : public IComponent {
    public:
        CRenderable_3D(const std::string &pathToModel, ZMaterial* material);
        CRenderable_3D(const CRenderable_3D &orig);
        virtual ~CRenderable_3D();

        // Functions of IComponent
        virtual gg::EMessageStatus processMessage(const Message &m);
        virtual void Init();
        virtual void Update();

        void changeMaterial(ZMaterial* material);
        //  Handler
        gg::EMessageStatus MHandler_SETPTRS();
        void setVisibility(bool flag);


    private:
        TNodo* _3DModel;
        Omicron* Surreal;

        CTransform* cTransform;
};

#endif
