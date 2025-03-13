#pragma once

#include <iostream>
#include <fstream>
#include "JsonData.h"
#include "ExecResult.h"
#include "Utilities.h"

class Json
{
public:

	Json();
	Json(char* jsonFilePath);
	virtual ~Json();

	void openJsonFile();
	void closeJsonFile();
	//void parse();
	void stringfy();

	EXEC_RESULT::EXEC_RESULT writeJsonDataToJsonFile(JsonData* jsonData);
	EXEC_RESULT::EXEC_RESULT parse(JsonData* jsonData);

	EXEC_RESULT::EXEC_RESULT checkCurlyBracket(char curlyBracket);
	EXEC_RESULT::EXEC_RESULT readKey(std::string& key);
	AbstractJsonDataType* readValue(JsonData* jsonData);

	void setJsonFilePath(char* jsonFilePath)
	{
		m_jsonFilePath = jsonFilePath;
	}

	char* getJsonFilePath()
	{
		return m_jsonFilePath;
	}

private:
	bool isJsonFileReadCompleted;

	std::fstream m_jsonFile;
	char* m_jsonFilePath;

};

