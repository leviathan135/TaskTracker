#pragma once
#include "AbstractJsonDataType.h"


class JsonNumberDataType : public AbstractJsonDataType
{
public:
    JsonNumberDataType();
    JsonNumberDataType(int jsonNumber);
    ~JsonNumberDataType();

    void write(std::fstream& jsonFile);
    void read(std::string numberValue);
    std::string getDataString();

    int getJsonNumber()
    {
        return m_jsonNumberInt;
    }

    void setJsonNumber(int jsonNumber)
    {
        m_jsonNumberInt = jsonNumber;
    }

private:
    int m_jsonNumberInt;
    double m_jsonNumberDouble;
    std::string m_jsonNumberString;
};

