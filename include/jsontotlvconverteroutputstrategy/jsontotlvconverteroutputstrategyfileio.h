#ifndef JSONTOTLVCONVERTEROUTPUTSTRATEGYFILEIO_H
#define JSONTOTLVCONVERTEROUTPUTSTRATEGYFILEIO_H

#include <sstream>
#include <fstream>


#include "jsontotlvconverteroutputstrategyinterface.h"

class JsonToTlvConverterOutputStrategyFileIo : public JsonToTlvConverterOutputStrategyInterface
{
public:
    JsonToTlvConverterOutputStrategyFileIo(int argc, char *argv[]);
    bool getline(std::string& line);

private:
    void setOutputSource(const std::string &_filename);

    std::ifstream m_inFile;
};

#endif // JSONTOTLVCONVERTEROUTPUTSTRATEGYFILEIO_H
