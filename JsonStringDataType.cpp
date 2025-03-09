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

EXEC_RESULT::EXEC_RESULT JsonStringDataType::read() { return EXEC_RESULT::SUCCESS; }

JsonStringDataType::~JsonStringDataType(){}