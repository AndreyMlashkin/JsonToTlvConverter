#ifndef JSONTOTLVCONVERTEROUTPUTSTRATEGYFILEIO_H
#define JSONTOTLVCONVERTEROUTPUTSTRATEGYFILEIO_H

#include <sstream>
#include <fstream>


#include "jsontotlvconverteroutputstrategyinterface.h"

class JsonToTlvConverterOutputStrategyFileIo : public JsonToTlvConverterOutputStrategyInterface
{
public:
    JsonToTlvConverterOutputStrategyFileIo(int argc, char *argv[], bool _truncate = true);
    virtual bool write(const char* _data, size_t _length) override;

private:
    void setOutputSource(const std::string &_filename, bool _truncate);

    std::ofstream m_outFile;
};

#endif // JSONTOTLVCONVERTEROUTPUTSTRATEGYFILEIO_H
