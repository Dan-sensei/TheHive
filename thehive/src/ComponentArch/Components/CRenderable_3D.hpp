#ifndef _CRENDERABLE_3D_H
#define _CRENDERABLE_3D_H

#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/Message.hpp>
#include <GameEngine/Model.hpp>
#include <map>
#include <iostream>

class CTransform;

class CRenderable_3D : public IComponent {
    friend class ObjectManager;
    public:
        virtual ~CRenderable_3D();

        // Functions of IComponent
        static void initComponent();
        virtual gg::EMessageStatus processMessage(const Message &m);
        virtual void initializeComponentData(const void* data);

        //  Handler
        gg::EMessageStatus MHandler_UPDATE();
        gg::EMessageStatus MHandler_SETPTRS();

    private:
        CRenderable_3D();
        CRenderable_3D(const CRenderable_3D &orig);
        Model _3DModel;

        CTransform* cTransform;
};

#endif
