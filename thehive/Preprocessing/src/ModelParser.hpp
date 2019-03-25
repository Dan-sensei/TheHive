#ifndef MODELPARSER_H
#define MODELPARSER_H

#include <string>

class ModelParser{

public:
    ModelParser();
    static void generateBinaryGG_StaticModel(const std::string &FileInput, const std::string& FileOutput, bool generateBoundingBox = true);
    static void generateBinaryGG_DynamicModel(const std::string &FileInput, const std::string& FileOutput, bool generateBoundingBox = true);

private:
    ModelParser(const ModelParser& orig) = delete;
    void operator=(ModelParser const& orig) = delete;

    static void parser(const std::string &FileInput, const std::string& FileOutput, unsigned int dyn = 0, bool generateBoundingBox= true);

};

#endif
