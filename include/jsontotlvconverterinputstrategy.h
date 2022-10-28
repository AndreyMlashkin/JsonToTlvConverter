#ifndef JSONTOTLVCONVERTERINPUTSTRATEGY_H
#define JSONTOTLVCONVERTERINPUTSTRATEGY_H

#include <memory>
#include <string>
#include <fstream>
#include <sstream>

class JsonToTlvConverterInputStrategyInterface
{
public:
    virtual bool getline(std::string& line) = 0;
};

class JsonToTlvConverterInputStrategyStdIo : public JsonToTlvConverterInputStrategyInterface
{
public:
    virtual bool getline(std::string& line) override;
};

class JsonToTlvConverterInputStrategyFileIo : public JsonToTlvConverterInputStrategyInterface
{
public:
    JsonToTlvConverterInputStrategyFileIo(int argc, char *argv[]);
    virtual bool getline(std::string& line) override;

private:
    void setOutputSource(const std::string &_filename, bool _truncate);
    void setInputSource(const std::string &_filename);

    std::ifstream m_inFile;
    std::ofstream m_outFile;
};


class JsonToTlvConverterInputStrategyFactory
{
public:
    static std::shared_ptr<JsonToTlvConverterInputStrategyInterface> createStrategy(int argc, char *argv[]);
private:

};

#endif // JSONTOTLVCONVERTERINPUTSTRATEGY_H
