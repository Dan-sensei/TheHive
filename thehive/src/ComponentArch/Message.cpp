#include "Message.hpp"

Message::Message(const gg::MessageType &type)
:mType(type), mData(nullptr)
{}

Message::Message(const gg::MessageType &type, void* data)
:mType(type), mData(data)
{}

Message::Message(const Message &orig){
    mType = orig.mType;
    mData = orig.mData;
}

Message::~Message(){}