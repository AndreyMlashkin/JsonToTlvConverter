#include <iostream>
#include <jsontotlvconverterinputstrategy/jsontotlvconverterinputstrategyfileio.h>


JsonToTlvConverterInputStrategyFileIo::JsonToTlvConverterInputStrategyFileIo(int argc, char *argv[])
{
    setInputSource(argv[1]);
}

bool JsonToTlvConverterInputStrategyFileIo::getline(std::string &line)
{
    std::getline(m_inFile, line);
    return !m_inFile.eof();
}

void JsonToTlvConverterInputStrategyFileIo::setInputSource(const std::string &_filename)
{
    m_inFile.open(_filename);
    if(!m_inFile.is_open())
    {
        std::cerr << "Can't open file " << _filename;
    }
}

