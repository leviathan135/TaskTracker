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

	if (strcmp("add", args[1]) == 0)
	{
		//call add function
		if (argc > 3 || argc < 3)
		{
			printError("You give invalid number of output");
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
			printError("You give invalid number of output");
			result = EXEC_RESULT::FAILURE;
		}
		else
		{
			result = update(args[2], args[3]);
		}
		std::cout << "Update fonksiyonu caðrildi" << std::endl;
	}
	else if (strcmp("delete", args[1]) == 0)
	{
		//call delete function 
		std::cout << "Delete fonksiyonu caðrildi" << std::endl;
	}
	else if (strcmp("mark-in-progress", args[1]) == 0)
	{
		//call mark-in-progress function
		std::cout << "mark-in-progress fonksiyonu caðrildi" << std::endl;
	}
	else if (strcmp("mark-done", args[1]) == 0)
	{
		//call mark-done
		std::cout << "mark-done fonksiyonu caðrildi" << std::endl;
	}
	else if (strcmp("list", args[1]) == 0)
	{
		//call list functions
		std::cout << "list fonksiyonlari caðrildi" << std::endl;
	}
	else 
	{
		std::cout << "You entered wrong function call! Try again!" << std::endl;
		result = EXEC_RESULT::FAILURE;
	}

	return result;
}

EXEC_RESULT::EXEC_RESULT Task::update(char* jsonID, char* newTask)
{
	EXEC_RESULT::EXEC_RESULT result = EXEC_RESULT::FAILURE;
	
	//Create jsonFileHandler instance
	JsonFileHandler jsonHandler;

	//@TODO: json dosyasini bulma isi daha sonra duzeltilecek.
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

	//@TODO: json dosyasini bulma isi daha sonra duzeltilecek.
	std::string examplejsonPath = std::string(getJsonPath()) + std::string("6.json");
	const char* jsonPath = examplejsonPath.data();
	//Set Json File Path before process
	jsonHandler.setJsonFilePath((char*)jsonPath);
	//Give keys of the json data to Handler. //@TODO: Buradaki key degerleri daha sonra bir json veya config dosyasi icerisinden okunabilir.
	std::vector<std::string> taskKeys = { "id", "description", "status", "createdAt", "updatedAt" };
	jsonHandler.setTaskKeys(taskKeys);

	result = jsonHandler.createNewTaskJson(newTask);
	
	return result;
}

