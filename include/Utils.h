#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <format>
#include <ctime>

namespace Utils
{
	std::string readFile(const char path[]);
	void writeFile(const char* path, auto content);
	void logger(const char* log);
};

