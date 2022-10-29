#include <iostream>
#include <jsontotlvconverterinputstrategy/jsontotlvconverterinputstrategystdio.h>

bool JsonToTlvConverterInputStrategyStdIo::getline(std::string &line)
{
    return std::getline(std::cin, line).eof();
}
