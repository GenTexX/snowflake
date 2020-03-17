#shader vertex

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec4 vertexcolor;

out vec4 vert_color;
out vec3 position;

void main() {

	gl_Position.xyz = vertexPosition_modelspace;
	gl_Position.w = 1.0;
	vert_color = vertexcolor;
	position = vertexPosition_modelspace;
}

#shader fragment

in vec4 vert_color;
in vec3 position;


float random2d(vec2 pos) {
	return fract(sin(dot(pos.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

out vec4 color;
void main() {

	float noise = (random2d(position.xy) - 0.35f) * 0.8;


	color = vert_color + noise;
}