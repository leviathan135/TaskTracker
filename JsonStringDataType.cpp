#include "JsonStringDataType.h"
/// @TODO Deneme amacli eklendi.
#include <iostream>
/// </summary>

JsonStringDataType::JsonStringDataType() : AbstractJsonDataType(){}

JsonStringDataType::JsonStringDataType(std::string jsonString) : AbstractJsonDataType()
{
	setJsonString(jsonString);
}

void JsonStringDataType::write(std::fstream& jsonFile)
{
	jsonFile << "\"";
	jsonFile << getJsonString();
	jsonFile << "\"";
}

void JsonStringDataType::read(std::fstream& jsonFile) 
{
	std::cout << "String okuma read metoduna girildi." << std::endl;
	char c;
	jsonFile >> c;
	while (c != '"')
	{
		m_jsonString = m_jsonString + c;
		jsonFile >> c;
	}

	std::cout << "JsonStringDataType icerisinde tutulan string: " << getJsonString() << std::endl;
}

JsonStringDataType::~JsonStringDataType(){}