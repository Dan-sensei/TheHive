#ifndef _MESSAGE_H
#define _MESSAGE_H


namespace gg{

    enum MessageType{
        M_UPDATE=0,
        M_SETPTRS,
        M_TRANSFORM,
        M_DAMAGE,
        MESSAGE_TYPE_COUNT
    };

}

struct Message{

        Message(const gg::MessageType &type);
        Message(const gg::MessageType &type, void* data);
        Message(const Message &orig);
        ~Message();

        gg::MessageType     mType;
        void*               mData;      // Guarda la información del mensaje (daño de una bala, string en mensaje, ids...)
                                        // como cada mensaje enviará una información diferente, habrá que castear el void
                                        // a lo que queramos.
                                        //
                                        //      Ej:  DamageData* info = static_cast<DamageData*>(message.mData);
                                        //
};

#endif
