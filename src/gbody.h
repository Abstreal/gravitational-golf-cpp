#pragma once

#include <godot_cpp/classes/character_body2d.hpp>
#include "regular_polygon2d.h"


using namespace godot;

class GBody : public CharacterBody2D {
    GDCLASS(GBody, CharacterBody2D);

    double mass;
    double density;
    double radius;

    Vector3 mdr_priorities;

    Vector2 initial_velocity;

protected:
    static void _bind_methods();

public:
    void set_mass(double mass_p);
    double get_mass();
    void set_density(double density_p);
    double get_density();
    void set_radius(double radius_p);
    double get_radius();

    void set_mass_noupdate(double mass_p);
    void set_density_noupdate(double density_p);
    void set_radius_noupdate(double radius_p);

    void set_mdr_priorities(Vector3 mdr_priorities_p);
    Vector3 get_mdr_priorities();

    void set_initial_velocity(Vector2 initial_velocity_p);
    Vector2 get_initial_velocity();

    void update_mdr(char what_changed);
    void apply_mass();
    void apply_density();
    void apply_radius(bool recalculate_radius);
    void apply_initial_velocity();

    GBody();

};