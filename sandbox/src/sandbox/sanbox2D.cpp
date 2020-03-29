#include "sanbox2D.h"

Sandbox2D::Sandbox2D() : m_CameraController(){


}

Sandbox2D::~Sandbox2D() {


}

void Sandbox2D::onEvent(SF::Event& event) {


}

void Sandbox2D::onUpdate() {

	SF::Renderer::beginScene(this->m_CameraController.getCamera());
	SF::Renderer::drawQuad(glm::vec2(0.0f, 0.0f), glm::vec2(0.5f, 0.5f), 20.0f, glm::vec4(0.2f, 0.4f, 0.2f, 1.0f));
	SF::Renderer::endScene();
	
}

void Sandbox2D::onAttach() {


}

void Sandbox2D::onDetach() {


}

void Sandbox2D::onImGuiRender() {


}