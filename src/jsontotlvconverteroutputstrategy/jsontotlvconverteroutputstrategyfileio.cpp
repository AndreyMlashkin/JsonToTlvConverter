#include <iostream>
#include <jsontotlvconverteroutputstrategy/jsontotlvconverteroutputstrategyfileio.h>


JsonToTlvConverterOutputStrategyFileIo::JsonToTlvConverterOutputStrategyFileIo(int argc, char *argv[], bool _truncate)
{
    setOutputSource(argv[2], _truncate);
}

bool JsonToTlvConverterOutputStrategyFileIo::write(const char *_data, size_t _length)
{
    m_outFile.write(_data, _length);
    return !m_outFile.bad();
}

void JsonToTlvConverterOutputStrategyFileIo::setOutputSource(const std::string &_filename, bool _truncate)
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

