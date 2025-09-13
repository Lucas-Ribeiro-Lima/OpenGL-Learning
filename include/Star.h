//
// Created by lucas.lima on 08/09/2025.
//

#ifndef OPENGL_LEARNING_STAR_H
#define OPENGL_LEARNING_STAR_H

#include "Corp.h"
#include "Material.h"

class Star : public Corp
{
    public:
        Star(MaterialData mat, float radius, float r, float t);
};


#endif //OPENGL_LEARNING_STAR_H