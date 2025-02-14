#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/character_body2d.hpp>

using namespace godot;

class GravityHandler : public Node {
    GDCLASS(GravityHandler, Node);

    double G;

protected:
    static void _bind_methods();

public:
    void set_G(double G_p);
    double get_G();

    Vector2 get_accel(Vector2 pos1, Vector2 pos2, double mass2);
    Vector2 get_total_accel(Node* body_node_ptr);
    void apply_accels(double delta);

    GravityHandler();
};