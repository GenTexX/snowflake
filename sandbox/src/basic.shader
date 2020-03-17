#shader vertex

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec4 vertexcolor;

out vec4 vert_color;

void main() {

	gl_Position.xyz = vertexPosition_modelspace;
	gl_Position.w = 1.0;
	vert_color = vertexcolor;
}

#shader fragment

in vec4 vert_color;

out vec4 color;
void main() {
	color = vert_color;
}