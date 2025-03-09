#pragma once

#include <vector>
#include <string>
#include "AbstractJsonDataType.h"

typedef enum JSON_DATA_TYPE
{
	JsonString = 1,
	JsonNumber = 2,
	JsonObject = 3,
	JsonArray  = 4,
	JsonBoolean = 5,
	JsonNull = 6
}JSON_DATA_TYPE;

class JsonData
{
public:
	JsonData();
	~JsonData();

	void insertKey(std::string key);
	void insertKeyVector(std::vector<std::string> keyVector);
	void insertValueVector(std::vector<AbstractJsonDataType*> valueVector);
	void insertValue(AbstractJsonDataType* jsonDataValue);

	void setKeys(std::vector<std::string> keys)
	{
		m_keys = keys;
	}

	std::vector<std::string>& getKeys()
	{
		return m_keys;
	}

	std::vector<AbstractJsonDataType*>& getValues()
	{
		return m_values;
	}

private:

	//Key of Json values
	std::vector<std::string> m_keys;
	//Pair of Json Data Type and itself
	std::vector<AbstractJsonDataType* > m_values;
};

