#ifndef JSONTOTLVCONVERTERINPUTSTRATEGY_H
#define JSONTOTLVCONVERTERINPUTSTRATEGY_H

#include <memory>
#include <string>
#include <fstream>
#include <sstream>

class JsonToTlvConverterInputStrategyInterface
{
public:
    virtual bool getline(std::string& line) = 0;
};


#endif // JSONTOTLVCONVERTERINPUTSTRATEGY_H
