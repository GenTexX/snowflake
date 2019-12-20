#include "sandbox.h"


Sandbox::Sandbox() {



}


Sandbox::~Sandbox() {

}

void Sandbox::init() {

	SF_TRACE("INIT SANDBOX");

	this->m_ApplicationWindow = new SF::Window();

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
