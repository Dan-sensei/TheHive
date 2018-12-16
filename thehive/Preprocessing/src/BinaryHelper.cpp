#include "BinaryHelper.hpp"

template<typename T>
std::ostream& GG_Write(std::ostream& _ostream, const T& value){
    return _ostream.write(reinterpret_cast<const char*>(&value), sizeof(T));
}

template<typename T>
std::istream & GG_Read(std::istream& _istream, T& value){
    return _istream.read(reinterpret_cast<char*>(&value), sizeof(T));
}
