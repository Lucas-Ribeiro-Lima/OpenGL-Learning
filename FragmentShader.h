#pragma once
#include <glad/glad.h>
#include "Shader.h"

class FragmentShader :
    public Shader
{
private:
    GLuint ID;
public:
    FragmentShader(const char* source);
    GLuint getId();
};

