#ifndef JSONTOTLVCONVERTEROUTPUTSTRATEGYFACTORY_H
#define JSONTOTLVCONVERTEROUTPUTSTRATEGYFACTORY_H

#include <memory>
#include <jsontotlvconverteroutputstrategy/jsontotlvconverteroutputstrategyinterface.h>

class JsonToTlvConverterOutputStrategyFactory
{
public:
    static std::shared_ptr<JsonToTlvConverterOutputStrategyInterface> createStrategy(int argc, char *argv[]);
private:

};

#endif // JSONTOTLVCONVERTEROUTPUTSTRATEGYFACTORY_H
