#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>

#include "rapidjson/error/en.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace rapidjson;

void writeToFile(const GenericDocument<ASCII<>>& record)
{
    std::ofstream ofs("output.json", std::ios::app);
    OStreamWrapper osw(ofs);

    Writer<OStreamWrapper> writer(osw);
    record.Accept(writer);
}

int main(int argc, char *argv[])
{
    auto* inputSource = &std::cin;
    std::ifstream inFile;

    if(argc >= 2)
    {
        char* filePath = argv[1];
        inFile.open(filePath);
        inputSource = &inFile;
    }

    GenericDocument<ASCII<>> inputRecord;
    std::string line;

    std::map<std::string, int> keyDict;
    auto findOrCreateKeyRecord = [&keyDict](const std::string& key) -> int
    {
        auto keyPoition = keyDict.find(key);
        if(keyPoition == keyDict.end())
        {
            keyDict[key] = keyDict.size();
            return keyDict.size() - 1;
        }
        return keyPoition->second;
    };

    int lineNumber = 0;
    while (std::getline(*inputSource, line))
    {
        ParseResult ok = inputRecord.Parse(line.c_str());
        if (!ok)
        {
            std::cout << "Not valid json: " << line << std::endl;
            std::cerr << "line=" << lineNumber << ", column=" << ok.Offset() << " JSON parse error: " << GetParseError_En(ok.Code());
            return 0;
        }

        for (auto iter = inputRecord.MemberBegin(); iter != inputRecord.MemberEnd(); ++iter)
        {
            const auto* keyValue = iter->name.GetString();
            int keyIndex = findOrCreateKeyRecord(keyValue);
            std::string keyCode = std::to_string(keyIndex);
            iter->name.SetString(keyCode.c_str(), keyCode.size(), inputRecord.GetAllocator());
        }
        writeToFile(inputRecord);
        ++lineNumber;
    }
    return 0;
}
