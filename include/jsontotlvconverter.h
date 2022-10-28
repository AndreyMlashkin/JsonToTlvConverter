#ifndef JSONTOTLVCONVERTER_H
#define JSONTOTLVCONVERTER_H

#include "jsontotlvconverterinputstrategy.h"
#include <ios>
#include <istream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <map>

class JsonToTlvConverter
{
public:
    JsonToTlvConverter() = delete;

    JsonToTlvConverter(const std::shared_ptr<JsonToTlvConverterInputStrategyInterface>& _interface);
    ~JsonToTlvConverter() = default;

    void setInputSource(const std::string& _filename);
    void setInputSource(std::istream& _iStream);

    void setOutputSource(const std::string& _filename, bool _truncate = true);
    void setOutputSource(std::ostream& _oStream);

    bool convertAll(bool _finalize = false);
    bool finalize();

private:
    int findOrCreateKeyRecord(const std::string& key);

    std::shared_ptr<JsonToTlvConverterInputStrategyInterface>& m_interface;

    std::istream* m_inputSteam;
    std::ostream* m_outputSteam;

    std::ifstream m_inFile;
    std::ofstream m_outFile;

    std::map<std::string, int> m_keyDict;
};

#endif // JSONTOTLVCONVERTER_H
