#pragma once
#include <glad.h>
#include <iostream>
#include "Utils.h"

class Texture
{
private:
	GLuint TEX = 0;
public:
	Texture(const char* texture);
	Texture(const char* texture, bool flip);
	GLuint getTex() const;
};

