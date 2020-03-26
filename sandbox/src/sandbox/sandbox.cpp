#include "sandbox.h"


void Sandbox::createWindow()
{

	this->m_ApplicationWindow = new SF::Window(800, 600, "SNOWFLAKE", 100, 100, SDL_WINDOW_RESIZABLE | SDL_WINDOW_FOREIGN);

	this->m_ApplicationWindow->setEventCallback(BIND_EVENT_FN(Application::onEvent));

}

Sandbox::Sandbox() : SF::Application() {}


Sandbox::~Sandbox() {}

void Sandbox::onEvent(SF::Event& e) {
	
	Application::onEvent(e);

	if (!e.m_Handled) {
		
		e.m_Handled = true;
	
	}
}

void Sandbox::init() {

	/*	
	*	Application::init() needs to be called, 
	*	cause in Appplications constructer, ther 
	*	is no Sandbox-Instance instaciated 
	*/
	SF::Application::init();

	SF_TRACE("INIT SANDBOX");

	this->m_ImGuiLayer = new SF::ImGuiLayer();
	this->pushOverLay(this->m_ImGuiLayer);

	this->pushLayer(new ExampleLayer());
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

}

void Sandbox::run() {

	SF_TRACE("RUN SANDBOX");

	SF::Shader* shader = SF::Shader::create("src/basic.shader");

	this->m_ImGuiLayer->addWindow(new ShaderEditorWindow(shader));

	shader->readFile();
	shader->compile();

	float verts[4 * 7] = {

	/*#### COORDS ####*/			/*###### COLOR #######*/
	-0.5f,	-0.5f, 0.0f,			1.0f, 0.5f, 0.2f, 1.0f,
	 0.5f,	-0.5f, 0.0f,			0.3f, 0.2f, 0.8f, 1.0f,
	 0.5f,	 0.5f, 0.0f,			0.4f, 0.7f, 0.1f, 1.0f,
	 -0.5f,	 0.5f, 0.0f,			0.2f, 1.0f, 0.6f, 1.0f

	};

	GLuint ind[6] = { 0, 1, 2, 0, 2, 3 };

	SF::VertexBuffer* vertexBuffer = SF::VertexBuffer::create(verts, sizeof(verts));
	SF::IndexBuffer* indexBuffer = SF::IndexBuffer::create(ind, sizeof(ind));
	
	SF::BufferLayout bl = {{SF::BufferElementType::Float3, "VertexCoordinates"}, {SF::BufferElementType::Float4, "VertexColor"}};

	vertexBuffer->setLayout(bl);
	
	SF::VertexArray* vao = SF::VertexArray::create();
	vao->addVertexBuffer(vertexBuffer);
	vao->setIndexBuffer(indexBuffer);


	//GameLoop
	while (!this->isRunning()) {

		SF::Renderer::beginScene();
		shader->bind();
		SF::Renderer::submit(vao);
		SF::Renderer::endScene();

		SF::Application::onUpdate();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}


}
