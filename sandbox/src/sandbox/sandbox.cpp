#include "sandbox.h"


Sandbox::Sandbox() {



}


Sandbox::~Sandbox() {

}

void Sandbox::onEvent(SF::Event& e) {


}

void Sandbox::init() {

	SF_TRACE("INIT SANDBOX");

	this->m_ApplicationWindow = new SF::Window(1024, 768, "SNOWFLAKE", 100, 100, SDL_WINDOW_RESIZABLE | SDL_WINDOW_FOREIGN);

	this->m_ApplicationWindow->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));

	glClearColor(0.5f, 0.2f, 0.1f, 1.0f);

}

void Sandbox::run() {

	SF_TRACE("RUN SANDBOX");

	//GameLoop
	while (!this->m_ApplicationWindow->shouldClose()) {

		this->m_ApplicationWindow->update();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}

}
