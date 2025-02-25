#include "gbody.h"
#include <godot_cpp/core/class_db.hpp>

#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/circle_shape2d.hpp>
#include "math_constants.h"

void GBody::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_mass", "mass_p"), &GBody::set_mass);
    ClassDB::bind_method(D_METHOD("get_mass"), &GBody::get_mass);
    ClassDB::bind_method(D_METHOD("set_density", "density_p"), &GBody::set_density);
    ClassDB::bind_method(D_METHOD("get_density"), &GBody::get_density);
    ClassDB::bind_method(D_METHOD("set_initial_velocity", "initial_velocity_p"), &GBody::set_initial_velocity);
    ClassDB::bind_method(D_METHOD("get_initial_velocity"), &GBody::get_initial_velocity);

    ClassDB::bind_method(D_METHOD("set_radius", "radius_p"), &GBody::set_radius);
    ClassDB::bind_method(D_METHOD("get_radius"), &GBody::get_radius);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "radius"), "set_radius", "get_radius");

    ClassDB::bind_method(D_METHOD("set_texture", "texture_p"), &GBody::set_texture);
    ClassDB::bind_method(D_METHOD("get_texture"), &GBody::get_texture);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "texture"), "set_texture", "get_texture");

    ClassDB::bind_method(D_METHOD("set_smaterial", "smaterial_p"), &GBody::set_smaterial);
    ClassDB::bind_method(D_METHOD("get_smaterial"), &GBody::get_smaterial);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "smaterial"), "set_smaterial", "get_smaterial");

    ClassDB::bind_method(D_METHOD("get_mdr_priorities"), &GBody::get_mdr_priorities);
    ClassDB::bind_method(D_METHOD("set_mdr_priorities", "mdr_priorities_p"), &GBody::set_mdr_priorities);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "mdr_priorities"), "set_mdr_priorities", "get_mdr_priorities");

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "mass"), "set_mass", "get_mass");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "density"), "set_density", "get_density");
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "initial_velocity"), "set_initial_velocity", "get_initial_velocity");
}

void GBody::set_mass_noupdate(double mass_p) {
    mass = mass_p;
}
void GBody::set_density_noupdate(double density_p) {
    if (density_p == 0) {return;}
    density = density_p;
}
void GBody::set_radius_noupdate(double radius_p) {
    if (radius_p == 0) {
        return;
    }
    radius = radius_p;
}

void GBody::set_mass(double mass_p) {
    set_mass_noupdate(mass_p);
    update_mdr('m');
}
double GBody::get_mass() {
    return mass;
}

void GBody::set_density(double density_p) {
    set_density_noupdate(density_p);
    update_mdr('d');
}
double GBody::get_density() {
    return density;
}

void GBody::set_radius(double radius_p) {
    set_radius_noupdate(radius_p);
    update_mdr('r');
}
double GBody::get_radius() {
    return radius;
}

void GBody::set_initial_velocity(Vector2 initial_velocity_p) {
    initial_velocity = initial_velocity_p;
    set_velocity(initial_velocity);
}
Vector2 GBody::get_initial_velocity() {
    return initial_velocity;
}

void GBody::set_texture(const Ref<Texture2D> texture_p) {
    texture = texture_p;
    if (texture_p != NULL) {
        apply_texture();
    }
}
Ref<Texture2D> GBody::get_texture() {
    return texture;
}

void GBody::set_smaterial(const Ref<ShaderMaterial> smaterial_p) {
    shader_material = smaterial_p;
    if (smaterial_p != NULL) {
        apply_smaterial();
    }
}
Ref<ShaderMaterial> GBody::get_smaterial() {
    return shader_material;
}
void GBody::apply_smaterial() {
    /*
    Assumes that get_child(1) exists and is the Sprite2D
    */
    Sprite2D* spr = Object::cast_to<Sprite2D>(get_child(1));
    spr->set_material(get_smaterial());
}

void GBody::apply_texture() {
    /*
    Assumes that:
        1. get_texture() != NULL
        2. get_child(1) is said Sprite2D
    */

    Sprite2D* spr = Object::cast_to<Sprite2D>(get_child(1));
    spr->set_texture(get_texture());
}

void GBody::apply_mass() {
    double new_mass = get_density() * PI * pow(get_radius(), 2);
    set_mass_noupdate(new_mass);
}

void GBody::apply_density() {
    double new_density = get_mass()/(PI * pow(get_radius(), 2));
    set_density_noupdate(new_density);
}

void GBody::apply_radius(bool recalculate_radius=true) {
    double new_radius = recalculate_radius ? sqrt(get_mass()/(PI * get_density())) : get_radius();

    CollisionShape2D* colshape = Object::cast_to<CollisionShape2D>(get_child(0));
    Ref<CircleShape2D> colshape_res = Object::cast_to<CircleShape2D>(*(colshape->get_shape()));
    colshape_res->set_radius(new_radius);

    Sprite2D* spr = Object::cast_to<Sprite2D>(get_child(1));
    spr->set_scale(Vector2(1, 1) * new_radius/8);

    set_radius_noupdate(new_radius);
}

void GBody::apply_initial_velocity() {
    set_velocity(get_initial_velocity());
}

void GBody::update_mdr(char what_changed) {
    /*
        The equation
            density = mass/(PI * {radius}^2) has to always be satisfied
        , and this function ensures that said satisfaction is the case.
    */
    
    const Vector3 priorities = get_mdr_priorities();
    /*
        The first entry: priority of mass
        The second entry: priority of density
        The third entry: priority of radius
    */

    switch(what_changed) {
        case 'm':
            if (priorities.y > priorities.z) {
                apply_radius();
            } else {
                apply_density();
            }
            break;
        case 'd':
            if (priorities.x > priorities.z) {
                apply_radius();
            } else {
                apply_mass();
            }
            break;
        case 'r':
            apply_radius(false);
            if (priorities.x > priorities.y) {
                apply_density();
            } else {
                apply_mass();
            }
            break;
    }

}

Vector3 GBody::get_mdr_priorities() {
    return mdr_priorities;
}
void GBody::set_mdr_priorities(Vector3 mdr_priorities_p) {
    mdr_priorities = mdr_priorities_p;
}

GBody::GBody() {
    mass = PI * 10000;
    density = 1;
    mdr_priorities = Vector3(0, 1, 2);
    set_initial_velocity(Vector2(0, 0));

    // Create children
    CollisionShape2D* colshape = memnew(CollisionShape2D);
    Ref<CircleShape2D> colshape_res = memnew(CircleShape2D);
    colshape_res->set_radius(get_radius());
    colshape->set_shape(colshape_res);
    add_child(colshape);

    Sprite2D* spr = memnew(Sprite2D);
    add_child(spr);

    set_texture(NULL);

    apply_radius();
}
