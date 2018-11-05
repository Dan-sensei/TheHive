#include "Message.hpp"

Message::Message(const gg::MessageType &type)
:mType(type)
{}

Message::Message(const gg::MessageType &type, void* data)
:mType(type), mData(data)
{}

Message::Message(const Message &orig){
    mType = orig.mType;
    mData = orig.mData;
}
