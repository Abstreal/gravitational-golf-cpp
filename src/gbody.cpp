#include "gbody.h"
#include <godot_cpp/core/class_db.hpp>

void GBody::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_mass", "mass_p"), &GBody::set_mass);
    ClassDB::bind_method(D_METHOD("get_mass"), &GBody::get_mass);
    ClassDB::bind_method(D_METHOD("set_density", "density_p"), &GBody::set_density);
    ClassDB::bind_method(D_METHOD("get_density"), &GBody::get_density);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "mass"), "set_mass", "get_mass");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "density"), "set_density", "get_density");
}

void GBody::set_mass(double mass_p) {
    mass = mass_p;
}
double GBody::get_mass() {
    return mass;
}

void GBody::set_density(double density_p) {
    density = density_p;
}
double GBody::get_density() {
    return density;
}

GBody::GBody() {
    mass = 1;
    density = 1;
}
