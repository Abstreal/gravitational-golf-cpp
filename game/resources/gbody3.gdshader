shader_type canvas_item;

uniform float radius = 0.5;
uniform float n = 3.0;
uniform float delta_n = 0.5;
uniform float delta_n_f = 2;

bool in_radius(vec2 uv) {
	float expr_naked = pow(abs(uv.x - 0.5), n + sin(delta_n_f * TIME) * delta_n) + pow(abs(uv.y - 0.5), n + sin(delta_n_f * TIME) * delta_n);
	float expr = pow(expr_naked, 1.0/n);
	return (expr <= radius);
}

void fragment() {
	if (in_radius(UV)) {
		COLOR = vec4(1, 1, 1, 1);
	} else {
		COLOR = vec4(1, 1, 1, 0);
	}
}