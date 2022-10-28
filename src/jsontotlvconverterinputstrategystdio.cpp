#include <iostream>
#include "../include/jsontotlvconverterinputstrategystdio.h"

bool JsonToTlvConverterInputStrategyStdIo::getline(std::string &line)
{
    return std::getline(std::cin, line).eof();
}
