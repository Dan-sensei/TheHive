#ifndef BDATA_H
#define BDATA_H

#include <string>
#include <Util.hpp>

class BData{
public:
    BData();
    BData(const BData &orig);
    ~BData();

    virtual int             getInt();
    virtual float           getFloat();
    virtual std::string     getString();
    virtual glm::vec3    getVector3f();
    virtual bool            getBool();


};

#endif
