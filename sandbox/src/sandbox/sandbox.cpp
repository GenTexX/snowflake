#include "sandbox.h"
#include "snowflake/core/core.h"
#include "sanbox2D.h"

void Sandbox::createWindow()
{

	this->m_ApplicationWindow = new SF::Window(800, 600, "SNOWFLAKE", 100, 100, SDL_WINDOW_RESIZABLE | SDL_WINDOW_FOREIGN);

	this->m_ApplicationWindow->setEventCallback(BIND_EVENT_FN(Application::onEvent));

}

Sandbox::Sandbox() : SF::Application() {}


Sandbox::~Sandbox() {}

void Sandbox::onEvent(SF::Event& e) {
	
	Application::onEvent(e);

	if (!e.m_Handled)	
		e.m_Handled = true;
	
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
	this->pushLayer(new Sandbox2D());

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

}

void Sandbox::run() {

	SF_TRACE("RUN SANDBOX");
	
	SF::Renderer::init();

	SF::OrthographicCameraController camController(0.0f, 0.0f);

	//GameLoop
	while (!this->isRunning()) {

		SF::Application::onUpdate();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}
	
}