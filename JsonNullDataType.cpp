#include "JsonNullDataType.h"


JsonNullDataType::JsonNullDataType()
{
	setDataString("");
}

void JsonNullDataType::write(std::fstream& file)
{
	//Do nothing..
}

void JsonNullDataType::read(std::string value)
{
	//Do nothing
}

std::string JsonNullDataType::getDataString()
{
	return m_stringfyedData;
}

void JsonNullDataType::setDataString(std::string stringfyedData)
{
	m_stringfyedData = stringfyedData;
}

JsonNullDataType::~JsonNullDataType(){}