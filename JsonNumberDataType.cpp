#include "JsonNumberDataType.h"

JsonNumberDataType::JsonNumberDataType(): AbstractJsonDataType() {}

JsonNumberDataType::JsonNumberDataType(int jsonNumber) : AbstractJsonDataType()
{
	setJsonNumber(jsonNumber);
}

JsonNumberDataType::JsonNumberDataType(std::string number) : AbstractJsonDataType()
{
	setDataString(number);
}

void JsonNumberDataType::write(std::fstream& jsonFile)
{
	jsonFile << getJsonNumber();
}

void JsonNumberDataType::read(std::string numberValue)
{
	setData(numberValue);
}

void JsonNumberDataType::setDataString(std::string stringfyedData)
{
	setData(stringfyedData);
}

std::string JsonNumberDataType::getDataString()
{
	
	return std::to_string(getJsonNumber());
}

void JsonNumberDataType::setData(std::string data)
{
	if (data.find('.') != std::string::npos) //That means number is double. //@TODO fonksiyonlari sonra yazilacak setter,getter.
	{
		m_jsonNumberDouble = std::stod(data);
	}
	else
	{
		m_jsonNumberInt = std::stoi(data);
	}
}

JsonNumberDataType::~JsonNumberDataType(){}
