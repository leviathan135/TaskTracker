#pragma once
#include "AbstractJsonDataType.h"


class JsonNumberDataType : public AbstractJsonDataType
{
public:

    JsonNumberDataType();
    JsonNumberDataType(int jsonNumber);
    JsonNumberDataType(std::string number);
    ~JsonNumberDataType();

    void write(std::fstream& jsonFile);
    void read(std::string numberValue);
    std::string getDataString();
    void setDataString(std::string stringfyedData);
    void setData(std::string data);

    int getJsonNumber()
    {
        return m_jsonNumberInt;
    }

    void setJsonNumber(int jsonNumber)
    {
        m_jsonNumberInt = jsonNumber;
    }

    JSON_DATA_TYPE getDataType()
    {
        return JSON_NUMBER;
    }

private:
    int m_jsonNumberInt;
    double m_jsonNumberDouble;
    std::string m_jsonNumberString;
};

