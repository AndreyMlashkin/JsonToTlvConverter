#include <iostream>
#include <jsontotlvconverteroutputstrategy/jsontotlvconverteroutputstrategyfileio.h>


JsonToTlvConverterOutputStrategyFileIo::JsonToTlvConverterOutputStrategyFileIo(int argc, char *argv[])
{
    setOutputSource(argv[1]);
}

bool JsonToTlvConverterOutputStrategyFileIo::getline(std::string &line)
{
    return std::getline(m_inFile, line).eof();
}

void JsonToTlvConverterOutputStrategyFileIo::setOutputSource(const std::string &_filename)
{
    m_inFile.open(_filename);
    if(!m_inFile.is_open())
    {
        std::cerr << "Can't open file " << _filename;
    }
}

