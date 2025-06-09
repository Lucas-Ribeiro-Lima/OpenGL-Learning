#pragma once
#include <glad/glad.h>
#include "Shader.h"
class VertexShader :
    public Shader
{
public:
    VertexShader(const char* source);
    GLuint getId();
};