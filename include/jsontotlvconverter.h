#ifndef JSONTOTLVCONVERTER_H
#define JSONTOTLVCONVERTER_H

#include "jsontotlvconverterinputstrategyinterface.h"
#include <ios>
#include <istream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <map>
#include <memory.h>

class JsonToTlvConverter
{
public:
    JsonToTlvConverter() = delete;

    JsonToTlvConverter(const std::shared_ptr<JsonToTlvConverterInputStrategyInterface>& _input);
    ~JsonToTlvConverter() = default;

    void setOutputSource(const std::string& _filename, bool _truncate = true);
    void setOutputSource(std::ostream& _oStream);

    bool convertAll(bool _finalize = false);
    bool finalize();

private:
    int findOrCreateKeyRecord(const std::string& key);

    std::shared_ptr<JsonToTlvConverterInputStrategyInterface> m_input;
    std::ostream* m_outputSteam;
    std::ofstream m_outFile;

    std::map<std::string, int> m_keyDict;
};

#endif // JSONTOTLVCONVERTER_H
