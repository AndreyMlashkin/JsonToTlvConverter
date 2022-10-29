#ifndef JSONTOTLVCONVERTER_H
#define JSONTOTLVCONVERTER_H

#include <map>
#include <memory>

class JsonToTlvConverterInputStrategyInterface;
class JsonToTlvConverterOutputStrategyInterface;

class JsonToTlvConverter
{
public:
    JsonToTlvConverter() = delete;

    JsonToTlvConverter(const std::shared_ptr<JsonToTlvConverterInputStrategyInterface>& _input,
                       const std::shared_ptr<JsonToTlvConverterOutputStrategyInterface>& _output);
    ~JsonToTlvConverter() = default;

    bool convertAll(bool _finalize = false);
    bool finalize();

private:
    int findOrCreateKeyRecord(const std::string& key);

    std::shared_ptr<JsonToTlvConverterInputStrategyInterface> m_input;
    std::shared_ptr<JsonToTlvConverterOutputStrategyInterface> m_output;

    std::map<std::string, int> m_keyDict;
};

#endif // JSONTOTLVCONVERTER_H
