#include "regular_polygon2d.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/array.hpp>

const float PI = 3.141592;

void RegularPolygon2D::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_nsides", "nsides_p"), &RegularPolygon2D::set_nsides);
    ClassDB::bind_method(D_METHOD("get_nsides"), &RegularPolygon2D::get_nsides);
    ClassDB::bind_method(D_METHOD("set_radius", "radius_p"), &RegularPolygon2D::set_radius);
    ClassDB::bind_method(D_METHOD("get_radius"), &RegularPolygon2D::get_radius);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "nsides"), "set_nsides", "get_nsides");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "radius"), "set_radius", "get_radius");
}

void RegularPolygon2D::set_nsides(int64_t nsides_p) {
    nsides = nsides_p;
    update_polygon();
}
int64_t RegularPolygon2D::get_nsides() {
    return nsides;
}

void RegularPolygon2D::set_radius(double radius_p) {
    radius = radius_p;
    update_polygon();
}
double RegularPolygon2D::get_radius() {
    return radius;
}

double RegularPolygon2D::get_delta_theta() {
    return 2 * PI/get_nsides();
}

Vector2 RegularPolygon2D::get_canon_vector() {
    return Vector2(0, get_radius());
}

void RegularPolygon2D::update_polygon() {
    size_t n = get_nsides();
    Array pol_arr = Array();
    Vector2 canonical_vertex = get_canon_vector();
    pol_arr.push_back(canonical_vertex);
    float delta_theta = get_delta_theta();
    for (size_t i = 1; i < n; ++i) {
        Vector2 loc = canonical_vertex.rotated(delta_theta * i);
        pol_arr.push_back(loc);
    }
    PackedVector2Array pol = PackedVector2Array(pol_arr);
    set_polygon(pol);
}

RegularPolygon2D::RegularPolygon2D() {
    set_nsides(10);
    set_radius(10);
}