#include "../include/jsontotlvconverter.h"

#include "jsontotlvconverteroutputstrategy/jsontotlvconverteroutputstrategyinterface.h"
#include "jsontotlvconverterinputstrategy/jsontotlvconverterinputstrategyinterface.h"
#include "rapidjson/document.h"
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>
#include "rapidjson/error/en.h"

#include "../3rd_party/TLV/cpp/tlv_box.h"

#include <iostream>


enum TlvTypesCode : unsigned char
{
    BOOL   = 1,
    INT    = 2,
    STRING = 3,

    RECORDS_SEPARATOR = 0xFE,
    DICTIONARY_START  = 0XFF,
};

typedef rapidjson::GenericDocument<rapidjson::ASCII<>> InputRecord;
typedef typeof(InputRecord::ValueType) JsonValue;

namespace
{

bool writeSimpleJsonValueToTlvFile(const JsonValue& value, tlv::TlvBox& box)
{
    assert(value.IsArray() == false);
    assert(value.IsObject() == false);

    if(value.IsBool())
        box.PutBoolValue(TlvTypesCode::BOOL, value.GetBool());
    else if(value.IsInt())
        box.PutIntValue(TlvTypesCode::INT, value.GetInt());
    else if(value.IsString())
        box.PutStringValue(TlvTypesCode::STRING, value.GetString());
    else
    {
        std::cerr << "can't handle rapid json Type " << value.GetType();
        return false;
    }
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
    int lineNumber = 0;
    std::string line;
    while (m_input->getline(line))
    {
        InputRecord inputRecord;

        rapidjson::ParseResult ok = inputRecord.Parse(line.c_str());
        if (!ok)
        {
            std::cout << "Not valid json: " << line << std::endl;
            std::cerr << "line=" << lineNumber << ", column=" << ok.Offset() << " JSON parse error: " << GetParseError_En(ok.Code());
            return false;
        }

        tlv::TlvBox box;
        for (auto iter = inputRecord.MemberBegin(); iter != inputRecord.MemberEnd(); ++iter)
        {
            const auto* keyValue = iter->name.GetString();
            int keyIndex = findOrCreateKeyRecord(keyValue);
            bool success = box.PutIntValue(TlvTypesCode::INT, keyIndex);
            if(!success)
                std::cerr << "Failed to servialize key for line=" << lineNumber;
            success = writeSimpleJsonValueToTlvFile(iter->value, box);
            if(!success)
                std::cerr << "Failed to serialize value for line=" << lineNumber << " key=" << iter->name.GetString();
        }

        box.PutNoValue(RECORDS_SEPARATOR);
        if (!box.Serialize())
        {
            std::cerr << "box Serialize Failed!\n";
            return false;
        }

        bool success = m_output->write(reinterpret_cast<const char*>(box.GetSerializedBuffer()), box.GetSerializedBytes());
        if(!success)
            std::cerr << "Failed to write line " << lineNumber << " on the disk";

        ++lineNumber;
    }
    if(_finalize)
        writeDictionary();

    return true;
}

bool JsonToTlvConverter::writeDictionary()
{
    tlv::TlvBox box;
    box.PutNoValue(DICTIONARY_START);

    for (auto&& [key, value] : m_keyDict)
    {
        bool success = box.PutStringValue(TlvTypesCode::STRING, key);
        if(!success)
            std::cerr << "Failed to write key, while writing a dictionary";

        success = box.PutIntValue(TlvTypesCode::INT, value);
        if(!success)
            std::cerr << "Failed to value, while writing a dictionary";
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
