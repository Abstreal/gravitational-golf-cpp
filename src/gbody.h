#pragma once

#include <godot_cpp/classes/character_body2d.hpp>
#include "regular_polygon2d.h"

using namespace godot;

class GBody : public CharacterBody2D {
    GDCLASS(GBody, CharacterBody2D);

    double mass;
    double density;

protected:
    static void _bind_methods();

public:
    void set_mass(double mass_p);
    double get_mass();

    void set_density(double density_p);
    double get_density();

    void apply_radius();

    GBody();
};