#ifndef JSONTOTLVCONVERTEROUTPUTSTRATEGYSTDIO_H
#define JSONTOTLVCONVERTEROUTPUTSTRATEGYSTDIO_H

#include <jsontotlvconverteroutputstrategy/jsontotlvconverteroutputstrategyinterface.h>

class JsonToTlvConverterOutputStrategyStdIo : public JsonToTlvConverterOutputStrategyInterface
{
public:
    JsonToTlvConverterOutputStrategyStdIo() = default;
    virtual bool write(const char* _data, size_t _length) override;
};

#endif // JSONTOTLVCONVERTEROUTPUTSTRATEGYSTDIO_H
