//
// Created by lucas.lima on 08/09/2025.
//

#include "../include/Star.h"
#include "Constants.h"

Star::Star(float radius, const char* tex, float r, float t) :
 Corp(radius, tex, r, t, Constants::FRAG_LIGHT) {}