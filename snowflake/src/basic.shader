#shader vertex

layout(location = 0) in vec3 aPos;

void main() {

	gl_Position = vec4(aPos, 1.0);

}

#shader fragment

void main() {

	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);

}