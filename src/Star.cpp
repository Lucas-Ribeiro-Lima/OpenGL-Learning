//
// Created by lucas.lima on 08/09/2025.
//

#include "../include/Star.h"
#include "Constants.h"

Star::Star(MaterialData mat, float radius, float r, float t) :
 Corp(mat, radius, r, t, Constants::FRAG_LIGHT) {}