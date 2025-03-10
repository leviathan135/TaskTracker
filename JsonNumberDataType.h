#pragma once
#include "AbstractJsonDataType.h"


class JsonNumberDataType : public AbstractJsonDataType
{
public:
    JsonNumberDataType();
    JsonNumberDataType(int jsonNumber);
    ~JsonNumberDataType();

    void write(std::fstream& jsonFile);
    void read(std::fstream& jsonFile);

    int getJsonNumber()
    {
        return m_jsonNumber;
    }

    void setJsonNumber(int jsonNumber)
    {
        m_jsonNumber = jsonNumber;
    }

private:
    int m_jsonNumber;
};

