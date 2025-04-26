#pragma once
#include "AbstractJsonDataType.h"

class JsonNullDataType : public AbstractJsonDataType
{
public: 
    JsonNullDataType();
    ~JsonNullDataType();

	void write(std::fstream& jsonFile);
	void read(std::string value);
	std::string getDataString();
	void setDataString(std::string stringfyedData);

	JSON_DATA_TYPE getDataType()
	{
		return JSON_NULL;
	}

private:
	std::string m_stringfyedData;
};

