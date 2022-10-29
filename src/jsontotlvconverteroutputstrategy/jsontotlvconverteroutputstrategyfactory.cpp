#include <cassert>

#include <jsontotlvconverteroutputstrategy/jsontotlvconverteroutputstrategyfactory.h>
#include <jsontotlvconverteroutputstrategy/jsontotlvconverteroutputstrategystdio.h>
#include <jsontotlvconverteroutputstrategy/jsontotlvconverteroutputstrategyfileio.h>

std::shared_ptr<JsonToTlvConverterOutputStrategyInterface> JsonToTlvConverterOutputStrategyFactory::createStrategy(int argc, char *argv[])
{
    if(argc == 1)
        return std::make_shared<JsonToTlvConverterOutputStrategyStdIo>();
    if(argc == 3)
        return std::make_shared<JsonToTlvConverterOutputStrategyFileIo>(argc, argv);
    else
        assert(false);
}

