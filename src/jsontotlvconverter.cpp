#include "../include/jsontotlvconverter.h"

#include "jsontotlvconverteroutputstrategy/jsontotlvconverteroutputstrategyinterface.h"
#include "jsontotlvconverterinputstrategy/jsontotlvconverterinputstrategyinterface.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>
#include "rapidjson/error/en.h"

#include "../3rd_party/TLV/cpp/tlv_box.h"

#include <iostream>


enum TlvTypesCode
{
    BOOL,
    INT,
    STRING
};

namespace
{

void writeJsonToFile(const rapidjson::GenericDocument<rapidjson::ASCII<>>& record)
{
    std::ofstream ofs("output.json", std::ios::app);
    rapidjson::OStreamWrapper osw(ofs);

    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
    record.Accept(writer);
}

bool writeTlvToFile(const rapidjson::GenericDocument<rapidjson::ASCII<>>& record, std::shared_ptr<JsonToTlvConverterOutputStrategyInterface> out)
{
    tlv::TlvBox box;
    for (auto iter = record.MemberBegin(); iter != record.MemberEnd(); ++iter)
    {
        const auto* key = iter->name.GetString();
        int keyNum = std::stoi(key);
        box.PutBoolValue(TlvTypesCode::INT, keyNum);

        if(iter->value.IsBool())
            box.PutBoolValue(TlvTypesCode::BOOL, iter->value.GetBool());
        else if(iter->value.IsInt())
            box.PutBoolValue(TlvTypesCode::INT, iter->value.GetInt());
        if(iter->value.IsString())
            box.PutBoolValue(TlvTypesCode::STRING, iter->value.GetString());
    }
    if (!box.Serialize())
    {
        std::cout << "box Serialize Failed!\n";
        return false;
    }

    out->write(reinterpret_cast<const char*>(box.GetSerializedBuffer()), box.GetSerializedBytes());
    return true;
}

}

JsonToTlvConverter::JsonToTlvConverter(const std::shared_ptr<JsonToTlvConverterInputStrategyInterface> &_input,
                                       const std::shared_ptr<JsonToTlvConverterOutputStrategyInterface> &_output) :
    m_input(_input),
    m_output(_output)
{

}

bool JsonToTlvConverter::convertAll(bool _finalize)
{
    rapidjson::GenericDocument<rapidjson::ASCII<>> inputRecord;
    int lineNumber = 0;
    std::string line;
    while (m_input->getline(line))
    {
        rapidjson::ParseResult ok = inputRecord.Parse(line.c_str());
        if (!ok)
        {
            std::cout << "Not valid json: " << line << std::endl;
            std::cerr << "line=" << lineNumber << ", column=" << ok.Offset() << " JSON parse error: " << GetParseError_En(ok.Code());
            return false;
        }

        for (auto iter = inputRecord.MemberBegin(); iter != inputRecord.MemberEnd(); ++iter)
        {
            const auto* keyValue = iter->name.GetString();
            int keyIndex = findOrCreateKeyRecord(keyValue);
            std::string keyCode = std::to_string(keyIndex);
            iter->name.SetString(keyCode.c_str(), keyCode.size(), inputRecord.GetAllocator());
        }
        writeJsonToFile(inputRecord);
        ::writeTlvToFile(inputRecord, m_output);
        ++lineNumber;
    }
    return true;
}

bool JsonToTlvConverter::finalize()
{
    tlv::TlvBox box;
    for (auto&& [key, value] : m_keyDict)
    {
        box.PutStringValue(TlvTypesCode::STRING, key);
        box.PutIntValue(TlvTypesCode::INT, value);
    }
    if (!box.Serialize())
    {
        std::cout << "Dictionary serialization failed!\n";
        return false;
    }

    m_output->write(reinterpret_cast<const char*>(box.GetSerializedBuffer()), box.GetSerializedBytes());
    return true;
}


int JsonToTlvConverter::findOrCreateKeyRecord(const std::string &key)
{
    auto keyPosition = m_keyDict.find(key);
    if(keyPosition == m_keyDict.end())
    {
        m_keyDict[key] = m_keyDict.size();
        return m_keyDict.size() - 1;
    }
    return keyPosition->second;
}
