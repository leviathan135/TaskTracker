#pragma once
#include <ctime>
#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

std::string getCurrentDateTime();
bool isFileExists(const std::string& fileName);
void printError(std::string error);