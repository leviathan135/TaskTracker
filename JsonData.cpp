#include "JsonData.h"

JsonData::JsonData()
{

}

void JsonData::insertKey(std::string key)
{
	m_keys.push_back(key);
}

void JsonData::insertKeyVector(std::vector<std::string> keyVector)
{
	m_keys = keyVector;
}

void JsonData::insertValue(AbstractJsonDataType* jsonDataValue)
{
	m_values.push_back(jsonDataValue);
}

void JsonData::insertValueVector(std::vector<AbstractJsonDataType*> valueVector)
{
	m_values = valueVector;
}

JsonData::~JsonData(){}