#ifndef JSONTOTLVCONVERTEROUTPUTSTRATEGYSTDIO_H
#define JSONTOTLVCONVERTEROUTPUTSTRATEGYSTDIO_H

#include <jsontotlvconverteroutputstrategy/jsontotlvconverteroutputstrategyinterface.h>

class JsonToTlvConverterOutputStrategyStdIo : public JsonToTlvConverterOutputStrategyInterface
{
public:
    JsonToTlvConverterOutputStrategyStdIo() = default;
    virtual bool getline(std::string& line) override;
};

#endif // JSONTOTLVCONVERTEROUTPUTSTRATEGYSTDIO_H
