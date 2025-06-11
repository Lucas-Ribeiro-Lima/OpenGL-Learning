#pragma once
#include <vector>

namespace Constants
{
	inline constexpr auto VSHADER_1 = "shader-1.glsl";
	inline constexpr auto FRAG_1 = "frag-1.glsl";
	inline constexpr auto FRAG_2 = "frag-2.glsl";
	inline constexpr auto TEX_EARTH_1 = "assets/grassblockside.png";
	inline constexpr auto TEX_PLANET_1 = "assets/earthMap.jpg";
	inline constexpr auto TEX_WATER_1 = "assets/water.jpg";

    inline std::vector<float> DISTANCES_PLANETS = {
        0.0f,     // Sol
        7.3f,     // Mercúrio
        13.7f,    // Vênus
        19.0f,    // Terra
        29.0f,    // Marte
        98.5f,    // Júpiter
        181.2f,   // Saturno
        363.1f,   // Urano
        500.0f    // Netuno
    };
};

