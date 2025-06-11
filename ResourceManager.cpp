#include "ResourceManager.h"

#define M_PI 3.1415

Camera& getCamera() {
    static Camera cam;
    return cam;
};

Geometry& getCubeGeometry() {
    std::vector<GLfloat> vertexesCube = {

    -0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f, 	0.0f, 0.0f, //0
     0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f, 	1.0f, 0.0f, //1
     0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f, 	1.0f, 1.0f, //2
    -0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f, 	0.0f, 1.0f, //3


    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f, 	0.0f, 0.0f, //4
     0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f, 	1.0f, 0.0f, //5
     0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f, 	1.0f, 1.0f, //6
    -0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f, 	0.0f, 1.0f  //7

    };

    std::vector<GLuint> indexesCube = {
            0, 1, 2, //0 Front
            0, 2, 3, //1 Front

            4, 5, 6, //2 Rear
            4, 6, 7, //3 Rear

            4, 0, 3, //4 Face-left
            4, 3, 7, //5 Face-left 

            3, 6, 7, //6 Face-up
            2, 3, 6, //7 Face-up

            2, 5, 6, //8 Face-right
            1, 2, 5, //9 Face-right

            0, 4, 5, //10 Bottom
            0, 1, 5, //11 Bottom
    };
    static Geometry instance{ vertexesCube, indexesCube };
    return instance;
}

Geometry& getSphereGeometry(float radius) {
    std::vector<GLfloat> vertexesSphere;
    std::vector<GLuint> indexesSphere;

    int stacks = 40;  // latitude
    int slices = 40;  // longitude

    for (int i = 0; i <= stacks; ++i) {
        float phi = (float)i / stacks * M_PI;
        float y = cosf(phi);
        float r = sinf(phi);

        for (int j = 0; j <= slices; ++j) {
            float theta = (float)j / slices * 2.0f * M_PI;
            float x = r * cosf(theta);
            float z = r * sinf(theta);

            // posição
            vertexesSphere.push_back(x * radius);
            vertexesSphere.push_back(y * radius);
            vertexesSphere.push_back(z * radius);

            // cor (apontando para fora)
            vertexesSphere.push_back(0.0f);
            vertexesSphere.push_back(0.0f);
            vertexesSphere.push_back(1.0f);

            // coordenadas de textura
            vertexesSphere.push_back((float)j / slices);
            vertexesSphere.push_back((float)i / stacks);
        }
    }

    // Índices (como um grid 2D que você "costura")
    for (int i = 0; i < stacks; ++i) {
        for (int j = 0; j < slices; ++j) {
            int first = (i * (slices + 1)) + j;
            int second = first + slices + 1;

            indexesSphere.push_back(first);
            indexesSphere.push_back(second);
            indexesSphere.push_back(first + 1);

            indexesSphere.push_back(second);
            indexesSphere.push_back(second + 1);
            indexesSphere.push_back(first + 1);
        }
    }

    static Geometry instance{ vertexesSphere, indexesSphere };
    return instance;
}

Texture& getEarthTexture(const char* tex) {
    static Texture instance{ tex };
    return instance;
}

Program& getDefaultProgram() {
    static Program instance{ Constants::VSHADER_1, Constants::FRAG_1 };
    return instance;
}

Program& getProgram(const char* frag) {
    static Program instance{ Constants::VSHADER_1, frag };
    return instance;
}