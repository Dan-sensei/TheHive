#ifndef _CRENDERABLE_3D_H
#define _CRENDERABLE_3D_H

#include <ComponentArch/IComponent.hpp>
#include <GameEngine/Model.hpp>

class CRenderable_3D : public IComponent {
    public:
        CRenderable_3D();
        CRenderable_3D(const CRenderable_3D &orig);
        virtual ~CRenderable_3D();

        // Functions of IComponent
        static void initComponent();
        virtual void initializeComponentData(const void* data);
        virtual gg::EMessageStatus processMessage();


    private:
        Model _3DModel;
};

#endif
