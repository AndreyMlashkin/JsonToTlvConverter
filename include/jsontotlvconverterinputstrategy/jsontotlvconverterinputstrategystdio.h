#ifndef JSONTOTLVCONVERTERINPUTSTRATEGYSTDIO_H
#define JSONTOTLVCONVERTERINPUTSTRATEGYSTDIO_H

#include <jsontotlvconverterinputstrategy/jsontotlvconverterinputstrategyinterface.h>

class JsonToTlvConverterInputStrategyStdIo : public JsonToTlvConverterInputStrategyInterface
{
public:
    JsonToTlvConverterInputStrategyStdIo() = default;
    virtual bool getline(std::string& line) override;
};

#endif // JSONTOTLVCONVERTERINPUTSTRATEGYSTDIO_H
