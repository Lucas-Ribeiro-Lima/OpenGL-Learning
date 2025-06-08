#pragma once
#include <string>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <functional>

namespace Utils
{
	std::string readFile(const char path[]);
	unsigned char* loadTexture(const char path[], int& width, int& heigth, int& nrChannels);
	void freeTexture(unsigned char* data);
};

