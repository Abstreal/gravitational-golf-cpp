#include "gbody.h"
#include <godot_cpp/core/class_db.hpp>

#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/circle_shape2d.hpp>
#include "math_constants.h"

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
    apply_radius();
}
double GBody::get_mass() {
    return mass;
}

void GBody::set_density(double density_p) {
    if (density_p == 0) {
        return;
    }
    density = density_p;
    apply_radius();
}
double GBody::get_density() {
    return density;
}

void GBody::apply_radius() {
    double radius = sqrt(get_mass()/(PI * get_density()));

    int l = get_child_count();
    if (l == 0) {
        CollisionShape2D* colshape = memnew(CollisionShape2D);
        Ref<CircleShape2D> colshape_res = memnew(CircleShape2D);
        colshape_res->set_radius(radius);
        colshape->set_shape(colshape_res);
    
        RegularPolygon2D* regpol = memnew(RegularPolygon2D);
        regpol->set_radius(radius);
    
        add_child(colshape);
        add_child(regpol);
    } else {
        CollisionShape2D* colshape = Object::cast_to<CollisionShape2D>(get_child(0));
        Ref<CircleShape2D> colshape_res = Object::cast_to<CircleShape2D>(*(colshape->get_shape()));
        colshape_res->set_radius(radius);

        RegularPolygon2D* regpol = Object::cast_to<RegularPolygon2D>(get_child(1));
        regpol->set_radius(radius);
    }
}

GBody::GBody() {
    mass = PI * 10000;
    density = 1;
    apply_radius();
}
