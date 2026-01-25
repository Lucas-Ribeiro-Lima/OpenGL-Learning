#pragma once

inline const char vertex_src[] = {
#embed "assets/valid_vertex_src.glsl"
    , '\0'};

inline const char fragment_src[] = {
#embed "assets/valid_fragment_src.glsl"
    , '\0'};

inline const char fragment_light_src[] = {
#embed "assets/frag_light_shader.glsl"
    , '\0'};

inline const char invalid_vertex_src[] = {
#embed "assets/invalid_vertex_src.glsl"
    , '\0'};

inline const char DUMMY_TEXTURE_PATH[] = "assets/black_pixel.png";
