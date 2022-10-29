#ifndef JSONTOTLVCONVERTERINPUTSTRATEGYFILEIO_H
#define JSONTOTLVCONVERTERINPUTSTRATEGYFILEIO_H

#include <sstream>
#include <fstream>


#include "jsontotlvconverterinputstrategyinterface.h"

class JsonToTlvConverterInputStrategyFileIo : public JsonToTlvConverterInputStrategyInterface
{
public:
    JsonToTlvConverterInputStrategyFileIo(int argc, char *argv[]);
    bool getline(std::string& line);

private:
    void setInputSource(const std::string &_filename);

    std::ifstream m_inFile;
};

#endif // JSONTOTLVCONVERTERINPUTSTRATEGYFILEIO_H
