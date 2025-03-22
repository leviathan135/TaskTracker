#pragma once

#include <vector>
#include <string>
#include "AbstractJsonDataType.h"
#include "JsonDataTypes.h"
/// <summary>
/// @TODO deneme amaçlý
#include <iostream>
/// </summary>


class JsonData
{
public:
	JsonData();
	~JsonData();

	void insertKey(std::string key);
	void insertKeyVector(std::vector<std::string> keyVector);
	void insertValueVector(std::vector<AbstractJsonDataType*> valueVector);
	void insertValue(AbstractJsonDataType* jsonDataValue);

	AbstractJsonDataType* operator[](std::string key) {
		std::vector<std::string>::iterator itr;
		int i = 0;
		for (itr = m_keys.begin(); itr != m_keys.end(); itr++)
		{
			if ((*itr) == key)
			{
				//keyFound;
				break;
			}
			else { i++; }
		}
		return (m_values.at(i));
	}

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

