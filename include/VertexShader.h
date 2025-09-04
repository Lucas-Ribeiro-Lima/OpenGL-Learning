#pragma once
#include <glad.h>
#include "Shader.h"

class VertexShader :
    public Shader
{
public:
    VertexShader(const char* source);
};