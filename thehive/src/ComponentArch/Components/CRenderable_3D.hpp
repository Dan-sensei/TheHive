#ifndef _CRENDERABLE_3D_H
#define _CRENDERABLE_3D_H

#include <ComponentArch/IComponent.hpp>
#include <GameEngine/Model.hpp>

class CRenderable_3D : public IComponent {
    friend class ObjectManager;
    public:
        virtual ~CRenderable_3D();

        // Functions of IComponent
        static void initComponent();
        virtual gg::EMessageStatus processMessage();
        virtual void initializeComponentData(const void* data);
        virtual void initAfterComponentAssigment();


    private:
        CRenderable_3D();
        CRenderable_3D(const CRenderable_3D &orig);
        Model _3DModel;
};

#endif
