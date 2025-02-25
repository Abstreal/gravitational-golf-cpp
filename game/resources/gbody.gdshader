shader_type canvas_item;

const float radius = 0.5;

bool in_radius(vec2 uv) {
	float expr = sqrt(pow(uv.x - radius, 2) + pow(uv.y - radius, 2));
	return (expr <= radius);
}

void fragment() {
	if (in_radius(UV)) {
		COLOR = vec4(1, 1, 1, 1);
	} else {
		COLOR = vec4(1, 1, 1, 0);
	}
}