#include <iostream>
#include "Task.h"

using namespace std;

char jsonPath [] = "C:/WS/TaskTrackerCLI/tasks/";

int main(int argc, char* args[])
{
	char* taskInput = NULL;

	//Start reading arguments from the i=1 position since args[0] is the program name
	taskInput = args[1];

	//cout << taskInput << endl;
	Task m_task = Task(taskInput, jsonPath);
	
	m_task.processTask(args, argc);




	return EXIT_SUCCESS;
}


