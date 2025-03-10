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

void JsonNumberDataType::read(std::fstream& jsonFile) { }

JsonNumberDataType::~JsonNumberDataType(){}
