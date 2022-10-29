#ifndef JSONTOTLVCONVERTEROUTPUTSTRATEGY_H
#define JSONTOTLVCONVERTEROUTPUTSTRATEGY_H

#include <memory>
#include <string>
#include <fstream>
#include <sstream>

class JsonToTlvConverterOutputStrategyInterface
{
public:
    virtual bool getline(std::string& line) = 0;
};


#endif // JSONTOTLVCONVERTEROUTPUTSTRATEGY_H
