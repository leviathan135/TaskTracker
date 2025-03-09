#pragma once
#include "AbstractJsonDataType.h"


class JsonNumberDataType : public AbstractJsonDataType
{
public:
    JsonNumberDataType();
    JsonNumberDataType(int jsonNumber);
    ~JsonNumberDataType();

    void write(std::fstream& jsonFile);
    EXEC_RESULT::EXEC_RESULT read();

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

