#pragma once
#include <glad/glad.h>
#include "Shader.h"

class FragmentShader :
    public Shader
{
public:
    FragmentShader(const char* source);
};

