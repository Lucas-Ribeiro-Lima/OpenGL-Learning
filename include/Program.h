#pragma once
#include <glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "FragmentShader.h"
#include "VertexShader.h"
#include "Light.h"
#include "Material.h"
#include "Utils.h"

class Program
{
private:
    char infoLog[512] = {};
    Light light;

    glm::mat4 projection;
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);

    glm::vec3 viewPos = glm::vec3(0.0f);

    int sucess = 0;
    GLuint ID = 0;

public:
    Program(const char* vertex, const char* fragment);
    Program& resetT();
    Program& scale(glm::vec3 scaleProps);
    Program& rotate(float degree, glm::vec3 rotateProps);
    Program& translate(glm::vec3 translateProps);
    void setCommonUniforms();
    void setUniform1I(const char name[], GLint value) const;
    void setUniform1UI(const char name[], GLuint value) const;
    void setUniform1f(const char name[], GLfloat value) const;
    void setUniform3fv(const char name[], glm::vec3& vec);
    void setUniform4fv(const char name[], glm::mat4& mat);
    void setUniform1i(const char name[], GLint value);
    void use();
    void errors();
};
