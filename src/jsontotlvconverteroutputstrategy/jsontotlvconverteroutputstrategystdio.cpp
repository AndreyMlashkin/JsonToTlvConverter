#include <iostream>
#include <jsontotlvconverteroutputstrategy/jsontotlvconverteroutputstrategystdio.h>

bool JsonToTlvConverterOutputStrategyStdIo::getline(std::string &line)
{
    return std::getline(std::cin, line).eof();
}
