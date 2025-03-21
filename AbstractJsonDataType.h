#pragma once
#include "ExecResult.h"
#include <string>
#include <fstream>

typedef enum JSON_DATA_TYPE
{
	JSON_STRING = 1,
	JSON_NUMBER = 2,
	JSON_OBJECT = 3,
	JSON_BOOLEAN = 4,
	JSON_NULL = 5,
	NOT_SPECIFIED = 6
}JSON_DATA_TYPE;

class AbstractJsonDataType
{
public:
	AbstractJsonDataType();
	AbstractJsonDataType(std::string);
	virtual ~AbstractJsonDataType();

	virtual void write(std::fstream& jsonFile) = 0;
	/// <summary>
	/// Value of key read as string and parse in read function.
	/// </summary>
	/// <param name="value"></param>
	virtual void read(std::string value) = 0;
	virtual std::string getDataString() = 0;
	virtual void setDataString(std::string stringfyedData) = 0;
	virtual JSON_DATA_TYPE getDataType() = 0;
};

