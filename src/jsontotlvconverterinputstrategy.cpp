#include "jsontotlvconverterinputstrategy.h"
#include <cassert>
#include <iostream>

std::shared_ptr<JsonToTlvConverterInputStrategyInterface> JsonToTlvConverterInputStrategyFactory::createStrategy(int argc, char *argv[])
{
    if(argc == 1)
        return std::make_shared<JsonToTlvConverterInputStrategyStdIo>();
    if(argc == 3)
        return std::make_shared<JsonToTlvConverterInputStrategyFileIo>(argc, argv);
    else
        assert(false);
}

bool JsonToTlvConverterInputStrategyStdIo::getline(std::string &line)
{
    return std::getline(std::cin, line).eof();
}

JsonToTlvConverterInputStrategyFileIo::JsonToTlvConverterInputStrategyFileIo(int argc, char *argv[])
{
    setInputSource(argv[1]);
    setOutputSource(argv[2], true);
}

void JsonToTlvConverterInputStrategyFileIo::setInputSource(const std::string &_filename)
{
    m_inFile.open(_filename);
    if(!m_inFile.is_open())
    {
        std::cerr << "Can't open file " << _filename;
    }
}

void JsonToTlvConverterInputStrategyFileIo::setOutputSource(const std::string &_filename, bool _truncate)
{
    auto mode = std::ios::binary;
    if(_truncate)
        mode = mode | std::ios::trunc;

    m_outFile.open(_filename, mode);
    if(!m_outFile.is_open())
    {
        std::cerr << "failed to open " << _filename;
    }
}
