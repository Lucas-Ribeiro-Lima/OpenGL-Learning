#pragma once
#include <string>

namespace Utils
{
	std::string readFile(const char path[]);
	unsigned char* loadTexture(const char path[], int& width, int& heigth, int& nrChannels);
	void freeTexture(unsigned char* data);
};

