// texture.cpp
#include "texture.hpp"

solid_color::solid_color(color c) {
    color_val = c;
}

solid_color::solid_color(double r, double g, double b) {
    // Call color-based constructor
    solid_color(color(r,g,b));
}

color solid_color::value(double u, double v, const point3& p) const {
    // Return singular color value for the texture
    return color_val;
}

checker::checker(shared_ptr<texture> _first, shared_ptr<texture> _second)
    : first(_first), second(_second) {}

checker::checker(color _first, color _second)
    : first(make_shared<solid_color>(_first)), second(make_shared<solid_color>(_second)) {}

color checker::value(double u, double v, const point3& p) const {
    /* Since sign of sine alternates, we can create a checker pattern by
     multiplying the sine of each dimension */
    double sines = sin(10*p.x())*sin(10*p.y())*sin(10*p.z());
    if (sines < 0) {
        return first->value(u, v, p);
    } else {
        return second->value(u, v, p);
    }
}