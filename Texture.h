#pragma once
#include <glad/glad.h>
#include <iostream>
#include "Utils.h"

class Texture
{
private:
	GLuint TEX = 0;
public:
	Texture(const char* texture);
	GLuint getTex() const;
};

