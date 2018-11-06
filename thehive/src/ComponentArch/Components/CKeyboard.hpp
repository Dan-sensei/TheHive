#ifndef _CKEYBOARD_H
#define _CKEYBOARD_H

#include <ComponentArch/IComponent.hpp>

class CKeyboard : public IComponent {
    friend class ObjectManager;
    public:
        virtual ~CKeyboard();

        static void initComponent();

        virtual gg::EMessageStatus processMessage();

    private:
        CKeyboard();
        CKeyboard(const CKeyboard &orig);
};

#endif
