#shader vertex
#version 410

layout(location = 0) in vec4 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexTexture_coord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec2 v_TexCoord;

void main() {

	vec4 vertexPosition_worldSpace = u_Model * vertexPosition_modelspace;

	gl_Position = u_Projection * ( u_View * vertexPosition_worldSpace);

	v_TexCoord = vertexTexture_coord;

}

#shader fragment
#version 410

in vec2 v_TexCoord;

out vec4 color;

uniform sampler2D u_Texture;

void main() {

	color = texture2D(u_Texture, v_TexCoord);

}
