#pragma once

class GLSLShaders
{
public:
    static constexpr const char* vertexShaderSource = R"glsl(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        void main()
        {
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        }
    )glsl";

    static constexpr const char* fragmentShaderSource = R"glsl(
        #version 330 core
        out vec4 FragColor;
        void main()
        {
            FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
        }
    )glsl";
};
