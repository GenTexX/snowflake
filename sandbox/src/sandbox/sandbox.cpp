#include "sandbox.h"


Sandbox::Sandbox() {

	this->pushLayer(new ExampleLayer());

}


Sandbox::~Sandbox() {

}

void Sandbox::onEvent(SF::Event& e) {
	
	Application::onEvent(e);

	if (!e.m_Handled) {
		SF_CORE_TRACE(e.toString());
		e.m_Handled = true;
	}
}

void Sandbox::init() {

	SF_TRACE("INIT SANDBOX");


	





	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

}

void Sandbox::run() {

	SF_TRACE("RUN SANDBOX");

	SF::OpenGLShader* shader = new SF::OpenGLShader("src/basic.shader");

	shader->readFile();
	shader->compile();

	float verts[3 * 7] = {

	/*#### COORDS ####*/			/*###### COLOR #######*/
	-0.5f,	-0.5f, 0.0f,			1.0f, 0.5f, 0.2f, 1.0f,
	 0.5f,	-0.5f, 0.0f,			0.3f, 0.2f, 0.8f, 1.0f,
	 0.0f,	 0.5f, 0.0f,			0.4f, 0.7f, 0.1f, 1.0f

	};

	GLuint ind[3] = { 0, 1, 2 };

	SF::VertexBuffer* vertexBuffer = SF::VertexBuffer::create(verts, sizeof(verts));
	SF::IndexBuffer* indexBuffer = SF::IndexBuffer::create(ind, sizeof(ind));
	
	SF::BufferLayout bl = {
		{SF::BufferElementType::Float3, "VertexCoordinates"}, {SF::BufferElementType::Float4, "VertexColor"}
	};

	vertexBuffer->setLayout(bl);
	
	SF::OpenGLVertexArray* vao = new SF::OpenGLVertexArray();
	vao->addVertexBuffer(vertexBuffer);
	vao->setIndexBuffer(indexBuffer);


	//GameLoop
	while (!this->windowShouldClose()) {
		
		vao->bind();
		shader->bind();

		

		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);




		SF::Application::update();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}

}
