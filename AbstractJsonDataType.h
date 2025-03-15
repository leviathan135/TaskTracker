#pragma once
#include "ExecResult.h"
#include <string>
#include <fstream>

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
};

