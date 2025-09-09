//
// Created by lucas.lima on 08/09/2025.
//

#ifndef OPENGL_LEARNING_STAR_H
#define OPENGL_LEARNING_STAR_H

#include "Corp.h"
#include "ResourceManager.h"

class Star : public Corp
{
    public:
        Star(float radius, const char* tex, float r, float t);
};


#endif //OPENGL_LEARNING_STAR_H