#include "JsonFileHandler.h"

JsonFileHandler::JsonFileHandler() : m_jsonFilePath(NULL) {

}

JsonFileHandler::~JsonFileHandler() {};

EXEC_RESULT::EXEC_RESULT JsonFileHandler::mark(char* markType, std::string& previousStatus)
{
	EXEC_RESULT::EXEC_RESULT result = EXEC_RESULT::FAILURE;

	//Check is json file exist with given id or not?
	if (!isFileExists(getJsonFilePath()))
	{
		printError("The json file you want to update does not exist.\n");
		return result;
	}
	//If json file exists, open json file.
	Json jsonFile;
	jsonFile.setJsonFilePath(getJsonFilePath());

	//Create jsonData to store  key and values.
	JsonData jsonData;

	result = jsonFile.parse(&jsonData);

	previousStatus = jsonData["status"]->getDataString();

	std::string markTypeOfTask;

	if (strcmp("mark-in-progress", markType) == 0)
	{
		markTypeOfTask = "in-progress";
	}
	else
	{
		markTypeOfTask = "done";
	}

	jsonData["status"]->setDataString(markTypeOfTask);
	jsonData["updatedAt"]->setDataString(getCurrentDateTime());

	//Write updated value to jsonfile again with trunc mode. jsonFilePath already set.
	jsonFile.openJsonFile();
	result = jsonFile.writeJsonDataToJsonFile(&jsonData);
	jsonFile.closeJsonFile();

	return result;
}

EXEC_RESULT::EXEC_RESULT JsonFileHandler::updateTaskJson(char* newTask)
{
	EXEC_RESULT::EXEC_RESULT result = EXEC_RESULT::FAILURE;

	//Check is json file exist with given id or not?
	if (!isFileExists(getJsonFilePath()))
	{
		printError("The json file you want to update does not exist.\n");
		
		return result;
	}

	//If json file exists, open json file.
	Json jsonFile;
	jsonFile.setJsonFilePath(getJsonFilePath());

	//Create jsonData to store  key and values.
	JsonData jsonData;

	jsonFile.parse(&jsonData);
	jsonData["description"]->setDataString(std::string(newTask));
	jsonData["updatedAt"]->setDataString(getCurrentDateTime());

	//Write updated value to jsonfile again with trunc mode. jsonFilePath already set.
	jsonFile.openJsonFile();
	jsonFile.writeJsonDataToJsonFile(&jsonData);
	jsonFile.closeJsonFile();


	return result;
}

EXEC_RESULT::EXEC_RESULT JsonFileHandler::createNewTaskJson(char* newTask, int newID)
{
	uint32_t result = 0;

	Json jsonFile;
	jsonFile.setJsonFilePath(getJsonFilePath());
	jsonFile.openJsonFile();

	//Create JsonData
	JsonData jsonData;
	jsonData.insertKeyVector(getTaskKeys());
	//Add each value of keys
	// First add task id, task description and status 
	result += addJsonNumber(jsonData, newID);
	result += addJsonString(jsonData, std::string(newTask));
	result += addJsonString(jsonData, "todo");

	std::string dateTime = getCurrentDateTime();

	//Second, add created and updated time 
	result += addJsonString(jsonData, dateTime);
	result += addJsonString(jsonData, dateTime);

	result += jsonFile.writeJsonDataToJsonFile(&jsonData);//This is actually json.strignfy function.

	jsonFile.closeJsonFile();

	if (result == 0)
	{
		std::cout << "Task added successfully (ID:" << newID << ")";
		return EXEC_RESULT::SUCCESS;
	}
	else {
		return EXEC_RESULT::FAILURE;
	}
}

EXEC_RESULT::EXEC_RESULT JsonFileHandler::createNewConfigJson()
{
	uint32_t result = 0;

	Json jsonFile;
	jsonFile.setJsonFilePath(getJsonFilePath());
	jsonFile.openJsonFile();

	//Create JsonData
	JsonData jsonData;
	jsonData.insertKeyVector(getTaskKeys());

	result += addJsonNumber(jsonData, 1);
	result += addJsonArray(jsonData, JSON_NUMBER);
	result += addJsonArray(jsonData, JSON_NUMBER);
	result += addJsonArray(jsonData, JSON_NUMBER);

	result += jsonFile.writeJsonDataToJsonFile(&jsonData);//This is actually json.strignfy function.
	//TODO write task information into the json file


	jsonFile.closeJsonFile();
	if (result == 0)
	{
		std::cout << "Config.json created first!";
		return EXEC_RESULT::SUCCESS;
	}
	else {
		return EXEC_RESULT::FAILURE;
	}
}

EXEC_RESULT::EXEC_RESULT JsonFileHandler::updateConfigJson(JsonData* configJsonData)
{
	uint32_t result = 0;

	Json jsonFile;
	jsonFile.setJsonFilePath(getJsonFilePath());
	jsonFile.openJsonFile();

	result += jsonFile.writeJsonDataToJsonFile(configJsonData);
	jsonFile.closeJsonFile();
	if (result == 0)
	{
		return EXEC_RESULT::SUCCESS;
	}
	else {
		return EXEC_RESULT::FAILURE;
	}
}

EXEC_RESULT::EXEC_RESULT JsonFileHandler::readConfigJson(JsonData* configJsonData)
{
	//If json file exists, open json file.
	Json jsonFile;
	jsonFile.setJsonFilePath(getJsonFilePath());

	return (jsonFile.parse(configJsonData));
}

EXEC_RESULT::EXEC_RESULT JsonFileHandler::addJsonArray(JsonData& jsonData, JSON_DATA_TYPE arrayDataType)
{
	AbstractJsonDataType* jsonArrayDataType = new JsonArrayDataType(arrayDataType);
	if (jsonArrayDataType != NULL)
	{
		jsonData.insertValue(jsonArrayDataType);
		return EXEC_RESULT::SUCCESS;
	}
	else { return EXEC_RESULT::FAILURE; }
}

EXEC_RESULT::EXEC_RESULT JsonFileHandler::addJsonString(JsonData& jsonData, std::string newTask)
{
	AbstractJsonDataType* jsonStringDataType = new JsonStringDataType(newTask);
	if (jsonStringDataType != NULL)
	{
		jsonData.insertValue(jsonStringDataType);
		return EXEC_RESULT::SUCCESS;
	}
	else { return EXEC_RESULT::FAILURE; }
}

EXEC_RESULT::EXEC_RESULT JsonFileHandler::addJsonNumber(JsonData& jsonData, int id)
{
	AbstractJsonDataType* jsonNumberDataType = new JsonNumberDataType(id);
	if (jsonNumberDataType != NULL)
	{
		jsonData.insertValue(jsonNumberDataType);
		return EXEC_RESULT::SUCCESS;
	}
	else { return EXEC_RESULT::FAILURE; }
}



