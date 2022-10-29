#include <iostream>
#include <jsontotlvconverteroutputstrategy/jsontotlvconverteroutputstrategystdio.h>

bool JsonToTlvConverterOutputStrategyStdIo::write(const char* _data, size_t _length)
{
    std::cout.write(_data, _length);
    return !std::cout.bad();
}
