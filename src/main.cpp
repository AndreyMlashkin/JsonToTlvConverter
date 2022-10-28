#include "jsontotlvconverter.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>
#include "rapidjson/error/en.h"

#include "../3rd_party/TLV/cpp/tlv_box.h"

#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace rapidjson;

enum TlvTypesCode
{
    BOOL,
    INT,
    STRING
};

void writeJsonToFile(const GenericDocument<ASCII<>>& record)
{
    std::ofstream ofs("output.json", std::ios::app);
    OStreamWrapper osw(ofs);

    Writer<OStreamWrapper> writer(osw);
    record.Accept(writer);
}

bool writeTlvToFile(const GenericDocument<ASCII<>>& record, const std::string& filename)
{
    std::ofstream ofs(filename, std::ios::trunc | std::ios::binary);
    if(!ofs.is_open())
    {
        std::cerr << "failed to open " << filename;
        return false;
    }
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

    ofs.write(reinterpret_cast<const char*>(box.GetSerializedBuffer()), box.GetSerializedBytes());
    return true;
}

int main(int argc, char *argv[])
{
    if(argc == 2 && std::strcmp(argv[1], "help") == 0 ||
       (argc != 1 && argc != 3))
    {
        std::cout << "Programm takes 0 or 2 arguments on start:\n"
                     "If you specify no arguments, programm will read data from standard input and write to standard output stream.\n"
                     "In other case, user shall specify input and output files\n";
        return 0;
    }

    JsonToTlvConverter converter;
    if(argc == 1)
    {
        converter.setInputSource(std::cin);
        converter.setOutputSource(std::cout);
    }
    else
    {
        converter.setInputSource(argv[1]);
        converter.setOutputSource(argv[2]);
    }

    converter.convertAll();

//    auto* inputSource = &std::cin;
//    std::ifstream inFile;

//    if(argc >= 2)
//    {
//        char* filePath = argv[1];
//        inFile.open(filePath);
//        inputSource = &inFile;
//    }

//    GenericDocument<ASCII<>> inputRecord;
//    std::string line;

//    std::map<std::string, int> keyDict;
//    auto findOrCreateKeyRecord = [&keyDict](const std::string& key) -> int
//    {
//        auto keyPosition = keyDict.find(key);
//        if(keyPosition == keyDict.end())
//        {
//            keyDict[key] = keyDict.size();
//            return keyDict.size() - 1;
//        }
//        return keyPosition->second;
//    };

//    // Write records:
//    int lineNumber = 0;
//    while (std::getline(*inputSource, line))
//    {
//        ParseResult ok = inputRecord.Parse(line.c_str());
//        if (!ok)
//        {
//            std::cout << "Not valid json: " << line << std::endl;
//            std::cerr << "line=" << lineNumber << ", column=" << ok.Offset() << " JSON parse error: " << GetParseError_En(ok.Code());
//            return 0;
//        }

//        for (auto iter = inputRecord.MemberBegin(); iter != inputRecord.MemberEnd(); ++iter)
//        {
//            const auto* keyValue = iter->name.GetString();
//            int keyIndex = findOrCreateKeyRecord(keyValue);
//            std::string keyCode = std::to_string(keyIndex);
//            iter->name.SetString(keyCode.c_str(), keyCode.size(), inputRecord.GetAllocator());
//        }
//        writeJsonToFile(inputRecord);
//        writeTlvToFile(inputRecord, argv[2]);
//        ++lineNumber;
//    }
    return 0;
}
