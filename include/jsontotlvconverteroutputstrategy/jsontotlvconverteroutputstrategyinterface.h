#ifndef JSONTOTLVCONVERTEROUTPUTSTRATEGY_H
#define JSONTOTLVCONVERTEROUTPUTSTRATEGY_H

#include <memory>
#include <string>
#include <fstream>
#include <sstream>

class JsonToTlvConverterOutputStrategyInterface
{
public:
    virtual bool write(const char* _data, size_t _length) = 0;
};


#endif // JSONTOTLVCONVERTEROUTPUTSTRATEGY_H
