
#shader vertex

layout(location = 0) in vec4 vertexPosition_modelspace;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main() {

	vec4 vertexPosition_worldSpace = u_Model * vertexPosition_modelspace;

	gl_Position = u_Projection * ( u_View * vertexPosition_worldSpace);

}


#shader fragment

out vec4 color;

void main() {
	color = vec4(0.8f, 0.4f, 0.2f, 1.0f);

}
