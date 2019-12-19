#include "sandbox.h"


Sandbox::Sandbox() : m_ApplicationWindow(nullptr) {



}


Sandbox::~Sandbox() {

}

void Sandbox::init() {

	SF_TRACE("INIT SANDBOX");

	this->m_ApplicationWindow = new SF::Window();


}

void Sandbox::run() {

	SF_TRACE("RUN SANDBOX");

	while (!this->m_ApplicationWindow->shouldClose()) {

		this->m_ApplicationWindow->update();

	}

}
