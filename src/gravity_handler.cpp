#include "gravity_handler.h"
#include <godot_cpp/core/class_db.hpp>

void GravityHandler::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_accel", "pos1", "pos2", "mass2"), &GravityHandler::get_accel);
    ClassDB::bind_method(D_METHOD("get_total_accel", "body_node"), &GravityHandler::get_total_accel);
    ClassDB::bind_method(D_METHOD("apply_accels", "delta"), &GravityHandler::apply_accels);
    ClassDB::bind_method(D_METHOD("set_G", "G_p"), &GravityHandler::set_G);
    ClassDB::bind_method(D_METHOD("get_G"), &GravityHandler::get_G);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "G"), "set_G", "get_G");
}

void GravityHandler::set_G(double G_p) {
    G = G_p;
}
double GravityHandler::get_G() {
    return G;
}

Vector2 GravityHandler::get_accel(Vector2 pos1, Vector2 pos2, double mass2) {
    Vector2 final = Vector2();
    Vector2 r_vec = pos2 - pos1;
    double r = r_vec.length();
    if (r == 0) {return Vector2();}

    double Gm_w = G * mass2;

    return Gm_w * (1/pow(r, 3)) * r_vec;
}

Vector2 GravityHandler::get_total_accel(Node* body_node_ptr) {
    size_t l = get_child_count();

    CharacterBody2D* self_body = Object::cast_to<CharacterBody2D>(body_node_ptr);
    Vector2 pos1 = self_body->get_global_position();

    Vector2 total = Vector2();
    for (size_t i = 0; i < l; ++i) {
        Node* other_body_as_node = get_child(i);
        CharacterBody2D* other_body = Object::cast_to<CharacterBody2D>(other_body_as_node);
        total += get_accel(pos1, other_body->get_global_position(), 1);
    }

    return total;
}

void GravityHandler::apply_accels(double delta) {
    size_t l = get_child_count();

    for (size_t j = 0; j < l; ++j) {
        Node* node_j = get_child(j);
        Vector2 accel_j = get_total_accel(node_j);
        CharacterBody2D* body_j = Object::cast_to<CharacterBody2D>(node_j);
        Vector2 body_j_initial_velocity = body_j->get_velocity();
        body_j->set_velocity(accel_j * delta);

        body_j->move_and_collide(body_j->get_velocity());
    }
}

GravityHandler::GravityHandler() {
    G = 1;
}
