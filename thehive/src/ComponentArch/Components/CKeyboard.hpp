#ifndef _CKEYBOARD_H
#define _CKEYBOARD_H

#include <ComponentArch/IComponent.hpp>
#include <cmath>

class CKeyboard : public IComponent {
    friend class ObjectManager;
    public:
        virtual ~CKeyboard();

        // Functions of IComponent
        static void initComponent();
        virtual gg::EMessageStatus processMessage();
        virtual void initializeComponentData(const void* data);
        virtual void initAfterComponentAssigment();



    private:
        CKeyboard();
        CKeyboard(const CKeyboard &orig) = delete;
};

#endif
