#ifndef BINARYHELPER_H
#define BINARYHELPER_H

#include <fstream>

class BinaryHelper{
    template<typename T>
    std::ostream& GG_Write(std::ostream& _ostream, const T& value);

    template<typename T>
    std::istream & GG_Read(std::istream& _istream, T& value);
};

#endif
