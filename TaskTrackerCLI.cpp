#include <iostream>
#include "Task.h"
#include "Utilities.h"

using namespace std;

char jsonPath [] = "C:/WS/TaskTrackerCLI/tasks/";

int main(int argc, char* args[])
{
	char* taskInput = NULL;

	//Start reading arguments from the i=1 position since args[0] is the program name
	taskInput = args[1];
	//TODO: arguman verilmezse while loop kurulup burada beklemesini sagla kullanicidan input alinarak program başlatilir.

	//cout << taskInput << endl;
	Task m_task = Task(taskInput, jsonPath);

	m_task.processTask(args, argc);




	return EXIT_SUCCESS;
}


