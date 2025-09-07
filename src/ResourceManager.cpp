#include "ResourceManager.h"

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

Geometry* getSphereGeometry(float radius) {
    static std::unordered_map<float, Geometry*> radiusMap;

    if (radiusMap.find(radius) != radiusMap.end()) {
        return radiusMap[radius];
    }

    std::vector<GLfloat> vertexesSphere;
    std::vector<GLuint> indexesSphere;

    int stacks = 40;  // latitude
    int slices = 40;  // longitude

    for (int i = 0; i <= stacks; ++i) {
        float phi = (float)i / stacks * M_PI;
        float y = cosf(phi) * radius;
        float r = sinf(phi) * radius;

        for (int j = 0; j <= slices; ++j) {
            float theta = (float)j / slices * 2.0f * M_PI;
            float x = r * cosf(theta);
            float z = r * sinf(theta);

            // posi��o
            vertexesSphere.push_back(x);
            vertexesSphere.push_back(y);
            vertexesSphere.push_back(z);

            // cor (apontando para fora)
            vertexesSphere.push_back(0.0f);
            vertexesSphere.push_back(0.0f);
            vertexesSphere.push_back(1.0f);

            // coordenadas de textura
            vertexesSphere.push_back(1.0f - ((float)j / slices));
            vertexesSphere.push_back(1.0f - ((float) i / stacks));
        }
    }

    // �ndices (como um grid 2D que voc� "costura")
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

    radiusMap.insert({ radius,  new Geometry{ vertexesSphere, indexesSphere } });

    return radiusMap[radius];
}

Texture* getTexture(const char* tex) {
    static std::unordered_map<const char*, Texture*> texMap;

    if (texMap.find(tex) != texMap.end()) {
        return texMap[tex];
    }

    texMap.insert({ tex, new Texture{ tex } });
    return texMap[tex];
}

Program& getDefaultProgram() {
    static Program instance{ Constants::VSHADER_1, Constants::FRAG_1 };
    return instance;
}

Program* getProgram(const char* frag) {
    static std::unordered_map<const char*, Program*> progMap;

    if (progMap.find(frag) != progMap.end()) {
        return progMap[frag];
    }

    progMap.insert({ frag, new Program{ Constants::VSHADER_1, frag } });

    return progMap[frag];
}