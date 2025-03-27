#include "Task.h"


Task::Task() : m_taskInput(nullptr), m_jsonPath(NULL) {
	
}

Task::Task(char* taskInput, char* jsonFilePath)
{
	setTaskInput(taskInput);
	setJsonPath(jsonFilePath);
}

Task::~Task(){};


EXEC_RESULT::EXEC_RESULT Task::processTask(char* args[], int argc)
{
	EXEC_RESULT::EXEC_RESULT result = EXEC_RESULT::FAILURE;

	configJsonPath = std::string(getJsonPath()) +  std::string("config.json");
	//Before processing the task, check config file exist or not.
	if (!isFileExists(configJsonPath))
	{
		createConfigJsonFile(configJsonPath);
		//createConfigJson
	}
	else 
	{
		//readConfigJson
		readConfigJsonFile(configJsonPath);
	}

	if (strcmp("add", args[1]) == 0)
	{
		//call add function
		if (argc > 3 || argc < 3)
		{
			printError("You give invalid number of input");
			result = EXEC_RESULT::FAILURE;
		}
		else 
		{
			result = add(args[2]);
		}

	}
	else if (strcmp("update", args[1]) == 0)
	{
		//call update function
		if (argc > 4 || argc < 4)
		{
			printError("You give invalid number of input");
			result = EXEC_RESULT::FAILURE;
		}
		else
		{
			result = update(args[2], args[3]);
		}
	}
	else if (strcmp("delete", args[1]) == 0)
	{
		if (argc > 3 || argc < 3)
		{
			printError("You give invalid number of input");
			result = EXEC_RESULT::FAILURE;
		}
		else
		{
			result = deleteTask(args[2]);
		}
	}
	else if ((strcmp("mark-in-progress", args[1]) == 0) || (strcmp("mark-done", args[1]) == 0))
	{
		if (argc > 3 || argc < 3)
		{
			printError("You give invalid number of input");
			result = EXEC_RESULT::FAILURE;
		}
		else
		{
			result = mark(args[1], args[2]);
		}
	}
	else if ((strcmp("list", args[1]) == 0))
	{
		if (args[2] == NULL)
		{
			//List all
			listToDo();
			listInProgress();
			listDone();
		}
		else if ((strcmp("done", args[2]) == 0))
		{
			//List done
			listDone();
		}
		else if ((strcmp("todo", args[2]) == 0))
		{
			//list todo
			listToDo();
		}
		else if ((strcmp("in-progress", args[2]) == 0))
		{
			//List in-progress
			listInProgress();
		}
		else if (argc > 4)
		{
			printError("You give invalid number of input");
			result = EXEC_RESULT::FAILURE;
		}
		else
		{
			printError("You entered invalid input");
			result = EXEC_RESULT::FAILURE;
		}
	}
	else 
	{
		std::cout << "You entered wrong function call! Try again!" << std::endl;
		result = EXEC_RESULT::FAILURE;
	}

	return result;
}

EXEC_RESULT::EXEC_RESULT Task::mark(char* markType, char* jsonID)
{
	EXEC_RESULT::EXEC_RESULT result = EXEC_RESULT::FAILURE;

	std::string previousStatus;

	//Create jsonFileHandler instance
	JsonFileHandler jsonHandler;

	std::string examplejsonPath = std::string(getJsonPath()) + std::string(jsonID) + std::string(".json");
	const char* jsonPath = examplejsonPath.data();
	//Set Json File Path before process
	jsonHandler.setJsonFilePath((char*)jsonPath);

	result = jsonHandler.mark(markType, previousStatus);

	//update config json. remove json ID from previosStatusarray and add to markType array
	((JsonArrayDataType*)m_configJson[previousStatus])->removeArrayValue(jsonID);

	AbstractJsonDataType* newStatusID = new JsonNumberDataType(jsonID);
	if (strcmp(markType, "mark-done") == 0)
	{
		((JsonArrayDataType*)m_configJson["done"])->insertArrayValue(newStatusID);
	}
	else if (strcmp(markType, "mark-in-progress") == 0)
	{
		((JsonArrayDataType*)m_configJson["in-progress"])->insertArrayValue(newStatusID);
	}
	
	//Write updated config json file to config.json
	//JsonFileHandler cjsonHandler;
	jsonHandler.setJsonFilePath((char*)(configJsonPath.data()));
	result = jsonHandler.updateConfigJson(&m_configJson);
	std::cout << "ConfigJson updated... " << std::endl;

	return result;
}

EXEC_RESULT::EXEC_RESULT Task::deleteTask(char* jsonID)
{
	EXEC_RESULT::EXEC_RESULT result = EXEC_RESULT::FAILURE;

	//Direclty delete file in here.

	std::string jsonPath = std::string(getJsonPath()) + std::string(jsonID) + std::string(".json");
	const char* jsonFilePath = jsonPath.data();

	//read status of the json file that will be removed, so that update config json
	std::string taskStatus;
	Json jsonFile;
	jsonFile.setJsonFilePath((char*)jsonFilePath);

	//Create jsonData to store  key and values.
	JsonData jsonData;

	jsonFile.parse(&jsonData);
	taskStatus = jsonData["status"]->getDataString();

	//update configJson array 

	((JsonArrayDataType*)m_configJson[taskStatus])->removeArrayValue(jsonID);

	//Write updated config json file to config.json
	JsonFileHandler jsonHandler;
	jsonHandler.setJsonFilePath((char*)(configJsonPath.data()));
	result = jsonHandler.updateConfigJson(&m_configJson);
	std::cout << "ConfigJson updated... " << std::endl;


	int status = remove(jsonFilePath);

	// Check if the file has been successfully removed
	if (status != 0) {
		perror("Error deleting file");
	}
	else {
		std::cout << "File successfully deleted" << std::endl;
	}

	return result;
}

EXEC_RESULT::EXEC_RESULT Task::update(char* jsonID, char* newTask)
{
	EXEC_RESULT::EXEC_RESULT result = EXEC_RESULT::FAILURE;
	
	//Create jsonFileHandler instance
	JsonFileHandler jsonHandler;

	std::string examplejsonPath = std::string(getJsonPath()) + std::string(jsonID) + std::string(".json");
	const char* jsonPath = examplejsonPath.data();
	//Set Json File Path before process
	jsonHandler.setJsonFilePath((char*)jsonPath);

	result = jsonHandler.updateTaskJson(newTask);

	return result;
}

EXEC_RESULT::EXEC_RESULT Task::add(char* newTask)
{
	//create new task in json format and the task name is newTask
	EXEC_RESULT::EXEC_RESULT result = EXEC_RESULT::FAILURE;
	JsonFileHandler jsonHandler;

	std::string newjsonPath = std::string(getJsonPath()) + m_configJson["newID"]->getDataString() + std::string(".json");
	const char* jsonPath = newjsonPath.data();
	//Set Json File Path before process
	jsonHandler.setJsonFilePath((char*)jsonPath);
	//Give keys of the json data to Handler.
	std::vector<std::string> taskKeys = { "id", "description", "status", "createdAt", "updatedAt" };
	jsonHandler.setTaskKeys(taskKeys);

	int newID = std::stoi(m_configJson["newID"]->getDataString());
	result = jsonHandler.createNewTaskJson(newTask, newID);
	//Update newID value and then update todo list before new ID written to config.json. Daha sonra bak config ici guncellenecek.
	AbstractJsonDataType* newTaskID = new JsonNumberDataType(newID);
	std::cout << "new ID is: " << newID << std::endl;
	((JsonArrayDataType*)m_configJson["todo"])->insertArrayValue(newTaskID);
	//Update new id 
	newID++;

	((JsonNumberDataType*)m_configJson["newID"])->setJsonNumber(newID);
	//Write updated config json file to config.json
	jsonHandler.setJsonFilePath((char*)(configJsonPath.data()));
	result = jsonHandler.updateConfigJson(&m_configJson);
	std::cout << "ConfigJson updated... " << std::endl;
	
	return result;
}

EXEC_RESULT::EXEC_RESULT Task::createConfigJsonFile(std::string configJsonPath)
{
	EXEC_RESULT::EXEC_RESULT result = EXEC_RESULT::FAILURE;
	JsonFileHandler jsonHandler;

	jsonHandler.setJsonFilePath((char*)(configJsonPath.data()));
	std::vector<std::string> taskKeys = { "newID", "done", "todo", "in-progress" };
	jsonHandler.setTaskKeys(taskKeys);
	result = jsonHandler.createNewConfigJson();
	return result;
}

EXEC_RESULT::EXEC_RESULT Task::readConfigJsonFile(std::string configJsonPath)
{
	EXEC_RESULT::EXEC_RESULT result = EXEC_RESULT::FAILURE;

	//Create jsonFileHandler instance
	JsonFileHandler jsonHandler;
	jsonHandler.setJsonFilePath((char*)(configJsonPath.data()));

	result = jsonHandler.readConfigJson(&m_configJson); //configJsonPath'i bu jsonData içerisine oku.

	return result;
}

void Task::listDone()
{
	std::cout << "done: " << m_configJson["done"]->getDataString() << std::endl;
}

void Task::listInProgress()
{
	std::cout << "in-progress: " << m_configJson["in-progress"]->getDataString()<<std::endl;
}

void Task::listToDo()
{
	std::cout << "todo: " << m_configJson["todo"]->getDataString() << std::endl;
}