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

EXEC_RESULT::EXEC_RESULT JsonNumberDataType::read() { return EXEC_RESULT::SUCCESS; }

JsonNumberDataType::~JsonNumberDataType(){}
