#include <iostream>
#include <jsontotlvconverterinputstrategyfileio.h>


JsonToTlvConverterInputStrategyFileIo::JsonToTlvConverterInputStrategyFileIo(int argc, char *argv[])
{
    setInputSource(argv[1]);
}

bool JsonToTlvConverterInputStrategyFileIo::getline(std::string &line)
{
    return std::getline(m_inFile, line).eof();
}

void JsonToTlvConverterInputStrategyFileIo::setInputSource(const std::string &_filename)
{
    m_inFile.open(_filename);
    if(!m_inFile.is_open())
    {
        std::cerr << "Can't open file " << _filename;
    }
}

