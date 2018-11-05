#ifndef _CKEYBOARD_H
#define _CKEYBOARD_H

#include <ComponentArch/IComponent.hpp>

class CKeyboard : public IComponent {
    public:
        CKeyboard();
        CKeyboard(const CKeyboard &orig);
        virtual ~CKeyboard();

        static void initComponent();

        virtual gg::EMessageStatus processMessage();

    private:
};

#endif
