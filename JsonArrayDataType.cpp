#include "JsonArrayDataType.h"

JsonArrayDataType::JsonArrayDataType()
{
	std::string s("[]");
	setDataString(s);
}

JsonArrayDataType::JsonArrayDataType(JSON_DATA_TYPE jsonArrayDataType)
{
	m_arrayDataType = jsonArrayDataType;
	std::string s("[]");
	setDataString(s);
}

JsonArrayDataType::~JsonArrayDataType() {}

void JsonArrayDataType::write(std::fstream& jsonFile)
{

	std::vector<AbstractJsonDataType*>::iterator itr;
	int i = 0;

	jsonFile << "[";
	for (itr = m_jsonArray.begin(); itr != m_jsonArray.end(); itr++,i++)
	{
		m_jsonArray.at(i)->write(jsonFile);

		if (itr != (m_jsonArray.end() - 1))
		{
			jsonFile << ",";
		}

	}
	jsonFile << "]";
	
}
//@TODO sil
#include <iostream>
void JsonArrayDataType::read(std::string arrayData) 
{
	//Remove first and last brackets []
	arrayData.erase(arrayData.begin());
	arrayData.erase(arrayData.end() - 1);

	if (!arrayData.empty())
	{
		//First obtain data type
		obtainArrayDataType(arrayData);
		parseArray(arrayData);
	}
	else
	{
		//There is nothing to parse add brackets again
		setDataString("[]");

	}
}

void JsonArrayDataType::parseArray(std::string arrayData)
{
	if (m_arrayDataType == JSON_BOOLEAN)
	{
		//parse boolean data
		//@TODO implement later
	}
	else if (m_arrayDataType == JSON_OBJECT)
	{
		//parse object data
		//@TODO: implement later
	}
	else if (m_arrayDataType == JSON_STRING)
	{
		//parse json string
		//@TODO implement later
	}
	else
	{
		//parse json number
		parseNumberData(arrayData);
	}

}

void JsonArrayDataType::parseNumberData(std::string numberData)
{
	AbstractJsonDataType* newData;
	std::string number;
	int i;
	std::cout << "bulunan sayilar: ";
	for (i = 0; i <= numberData.size(); i++)
	{
		if (numberData[i] == ',' || i==numberData.size())
		{
			newData = new JsonNumberDataType(number);
			insertArrayValue(newData);
			std::cout << number << " ";
			number.clear();
			continue;
		}
		number = number + numberData[i];
		
	}
	std::cout<<"updated array is "<<getDataString()<< std::endl;
}

void JsonArrayDataType::obtainArrayDataType(std::string arrayData)
{
	if (arrayData[0] == '"')
	{
		//This array of string
		m_arrayDataType = JSON_STRING;
	}
	else if (arrayData[0] == '{')
	{
		m_arrayDataType = JSON_OBJECT;
	}
	else if (arrayData[0] == 't' || arrayData[0] == 'n')
	{
		m_arrayDataType = JSON_NULL;
	}
	else
	{
		m_arrayDataType = JSON_NUMBER;
	}
}

std::string JsonArrayDataType::getDataString()
{
	if (!m_stringyfedJsonArray.empty())
		return m_stringyfedJsonArray;
	else
	{
		std::string s("Array is not read!");
		return s;
	}
}

void JsonArrayDataType::setDataString(std::string arrayData)
{
	m_stringyfedJsonArray = arrayData;
}

void JsonArrayDataType::removeArrayValue(std::string value)
{
	uint32_t i;
	for (i = 0; i < m_jsonArray.size(); i++)
	{
		if ((m_jsonArray.at(i))->getDataString() != value)
		{
			i++;
		}
		else
		{
			break;
		}
	}
	if (i < m_jsonArray.size())
	{
		m_jsonArray.erase(m_jsonArray.begin() + i);
		//update stringfyed array 
		std::string updatedStringfyedArray;
		updatedStringfyedArray = getDataString();
		size_t index = updatedStringfyedArray.find(value);

		if (updatedStringfyedArray[index - 1] == ',')
		{
			updatedStringfyedArray.erase(updatedStringfyedArray.begin() + index - 1, updatedStringfyedArray.begin() + index + 1); // Remove the range [first, last)
		}
		else
		{
			updatedStringfyedArray.erase(updatedStringfyedArray.begin() + index, updatedStringfyedArray.begin() + index + 1);
		}
		setDataString(updatedStringfyedArray);
	}
}

void JsonArrayDataType::insertArrayValue(AbstractJsonDataType* jsonDataValue)
{

	if (m_arrayDataType != jsonDataValue->getDataType() && m_arrayDataType != NOT_SPECIFIED)
	{
		throw("Array Data Type and input data type does not match. Ensure you give the right data type value");
	}
	else
	{
		if (m_arrayDataType == NOT_SPECIFIED)
		{
			std::cout << "Array Data Type is not specified! Adjusting with the same data type with inserting value !!";
			m_arrayDataType = jsonDataValue->getDataType();
		}
		m_jsonArray.push_back(jsonDataValue);
		//update stringfyed data
		std::string s(jsonDataValue->getDataString());
		if (getDataString().size() != 2) //If array is empty, that means only brackets []
		{
			s = "," + s;
		}

		std::string dataString(getDataString());
		dataString.insert(dataString.size() - 1, s);
		setDataString(dataString);

	}

	
}
