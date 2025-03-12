#include "JsonStringDataType.h"

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

void JsonStringDataType::read(std::string stringValue)
{
	//Remove double quotes beginning and end of the string
	stringValue.erase(stringValue.begin());
	stringValue.erase(stringValue.end() - 1);
	
	setJsonString(stringValue);
}

JsonStringDataType::~JsonStringDataType(){}