#pragma once

#include "ExecResult.h"
#include <iostream>
#include "Json.h"
#include "JsonData.h"
#include "JsonNumberDataType.h"
#include "JsonStringDataType.h"
#include <string>
#include "Utilities.h"



class JsonFileHandler
{
public:
	JsonFileHandler();
	~JsonFileHandler();

	
	EXEC_RESULT::EXEC_RESULT createNewTaskJson(char* newTask);
	EXEC_RESULT::EXEC_RESULT updateTaskJson(char* newTask);
	EXEC_RESULT::EXEC_RESULT mark(char* markType);

	EXEC_RESULT::EXEC_RESULT addJsonNumber(JsonData& jsonData, int id);
	EXEC_RESULT::EXEC_RESULT addJsonString(JsonData& jsonData, std::string jsonString);

	void setJsonFilePath(char* jsonFilePath)
	{
		m_jsonFilePath = jsonFilePath;
	}

	char* getJsonFilePath()
	{
		return m_jsonFilePath;
	}

	void setTaskKeys(std::vector<std::string> keys)
	{
		m_taskKeys = keys;
	}
	
	std::vector<std::string> getTaskKeys()
	{
		return m_taskKeys;
	}

private:

	char* m_jsonFilePath;
	std::vector<std::string> m_taskKeys;

};

