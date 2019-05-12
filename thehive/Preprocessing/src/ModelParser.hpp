#ifndef MODELPARSER_H
#define MODELPARSER_H

#include <string>

class ModelParser{

public:
    ModelParser();
    static void generateBinaryGG_StaticModel(const std::string &FileInput, const std::string& FileOutput);
    static void generateBinaryGG_DynamicModel(const std::string &FileInput, const std::string& FileOutput);

private:
    ModelParser(const ModelParser& orig) = delete;
    void operator=(ModelParser const& orig) = delete;

    static void parser(const std::string &FileInput, const std::string& FileOutput, unsigned int dyn = 0);

};

#endif
