#pragma once
#include "AbstractJsonDataType.h"


class JsonStringDataType : public AbstractJsonDataType
{
public:
	JsonStringDataType();
	JsonStringDataType(std::string jsonString);
	~JsonStringDataType();

	void write(std::fstream& jsonFile);
	EXEC_RESULT::EXEC_RESULT read();

	std::string getJsonString()
	{
		return m_jsonString;
	}

	void setJsonString(std::string jsonString)
	{
		m_jsonString = jsonString;
	}

private:
	std::string m_jsonString;
};


