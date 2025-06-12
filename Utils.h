#pragma once
#include <string>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <fstream>
#include <sstream>
#include <format>
#include <ctime>
#include "Constants.h"

namespace Utils
{
	std::string readFile(const char path[]);
	void writeFile(const char* path, auto content);
	void logger(const char* log);
	unsigned char* loadTexture(const char path[], int& width, int& heigth, int& nrChannels, bool flip = true);
	void freeTexture(unsigned char* data);
};

