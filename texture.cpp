// texture.cpp
#include "texture.hpp"

solid_color::solid_color(color c) {
    color_val = c;
}

solid_color::solid_color(double r, double g, double b) {
    // Call color-based constructor
    solid_color(color(r,g,b));
}

color solid_color::value(double u, double v, const point3& p) {
    // Return singular color value for the texture
    return color_val;
}
