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
	virtual void read(std::fstream& jsonFile) = 0;
};

