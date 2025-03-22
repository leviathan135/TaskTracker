#include "Utilities.h"


std::string getCurrentDateTime()
{
	std::string dateTime;
	//Get Current Date and Time. Taken From https://stackoverflow.com/questions/38034033/c-localtime-this-function-or-variable-may-be-unsafe
	time_t rawtime;

	time(&rawtime);
	std::tm bt{};
	localtime_s(&bt, &rawtime);

	char buf[64];
	const std::string& fmt = "%F %T";

	dateTime = { buf, std::strftime(buf, sizeof(buf), fmt.c_str(), &bt) };

	return dateTime;
}

bool isFileExists(const std::string& filename)
{
	//This function needs C++17 or above.
	namespace fs = std::filesystem;
	return std::filesystem::exists(filename);
}

void printError(std::string error)
{
	std::cout << "\033[" << 31 << "m";
	std::cerr << error<<std::endl;
	std::cout << "\033[" << 0 << "m";
}