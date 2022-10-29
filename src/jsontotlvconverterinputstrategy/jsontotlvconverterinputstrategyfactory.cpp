#include <cassert>

#include <jsontotlvconverterinputstrategy/jsontotlvconverterinputstrategyfactory.h>
#include <jsontotlvconverterinputstrategy/jsontotlvconverterinputstrategystdio.h>
#include <jsontotlvconverterinputstrategy/jsontotlvconverterinputstrategyfileio.h>

std::shared_ptr<JsonToTlvConverterInputStrategyInterface> JsonToTlvConverterInputStrategyFactory::createStrategy(int argc, char *argv[])
{
    if(argc == 1)
        return std::make_shared<JsonToTlvConverterInputStrategyStdIo>();
    if(argc == 3)
        return std::make_shared<JsonToTlvConverterInputStrategyFileIo>(argc, argv);
    else
        assert(false);
}

