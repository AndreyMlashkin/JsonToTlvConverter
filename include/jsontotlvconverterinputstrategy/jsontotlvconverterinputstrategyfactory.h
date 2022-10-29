#ifndef JSONTOTLVCONVERTERINPUTSTRATEGYFACTORY_H
#define JSONTOTLVCONVERTERINPUTSTRATEGYFACTORY_H

#include <memory>
#include <jsontotlvconverterinputstrategy/jsontotlvconverterinputstrategyinterface.h>

class JsonToTlvConverterInputStrategyFactory
{
public:
    static std::shared_ptr<JsonToTlvConverterInputStrategyInterface> createStrategy(int argc, char *argv[]);
private:

};

#endif // JSONTOTLVCONVERTERINPUTSTRATEGYFACTORY_H
