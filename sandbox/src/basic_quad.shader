#shader vertex
#version 410

layout(location = 0) in vec4 vertexPosition_modelspace;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main() {

	vec4 vertexPosition_worldSpace = u_Model * vertexPosition_modelspace;

	gl_Position = u_Projection * ( u_View * vertexPosition_worldSpace);

}


#shader fragment
#version 410

out vec4 color;

uniform vec4 u_Color;

void main() {

	color = u_Color;

}
