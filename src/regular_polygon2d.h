#pragma once

#include <stdint.h>
#include <godot_cpp/classes/polygon2d.hpp>

using namespace godot;

class RegularPolygon2D : public Polygon2D {
    GDCLASS(RegularPolygon2D, Polygon2D);

    int64_t nsides;
    double radius;

protected:
    static void _bind_methods();

public:

    void set_nsides(int64_t nsides_p);
    int64_t get_nsides();

    void set_radius(double radius_p);
    double get_radius();

    void update_polygon();

    RegularPolygon2D();
};