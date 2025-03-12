#include "JsonNumberDataType.h"

JsonNumberDataType::JsonNumberDataType(): AbstractJsonDataType() {}

JsonNumberDataType::JsonNumberDataType(int jsonNumber) : AbstractJsonDataType()
{
	setJsonNumber(jsonNumber);
}


void JsonNumberDataType::write(std::fstream& jsonFile)
{
	jsonFile << getJsonNumber();
}

void JsonNumberDataType::read(std::string numberValue)
{
	
	if (numberValue.find('.') != std::string::npos) //That means number is double. //@TODO fonksiyonlari sonra yazilacak setter,getter.
	{
		m_jsonNumberDouble = std::stod(numberValue);
	}
	else
	{
		m_jsonNumberInt = std::stoi(numberValue);
	}
}

JsonNumberDataType::~JsonNumberDataType(){}
