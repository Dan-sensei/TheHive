#ifndef MODELPARSER_H
#define MODELPARSER_H

#include <string>

class ModelParser{

public:
    ModelParser();
    static void generateBinaryGG_Model(const std::string &FileInput, const std::string& FileOutput);

private:
    ModelParser(const ModelParser& orig) = delete;
    void operator=(ModelParser const& orig) = delete;


};

#endif
