#include "sanbox2D.h"
#include "snowflake/input/input.h"

Sandbox2D::Sandbox2D() : m_CameraController(){


}

Sandbox2D::~Sandbox2D() {


}

void Sandbox2D::onEvent(SF::Event& event) {


}

void Sandbox2D::onUpdate() {

	if (SF::Input::IsKeyPressed(SF::KeyCode::SFK_w))
		this->m_CameraController.moveY(0.03f);
	if (SF::Input::IsKeyPressed(SF::KeyCode::SFK_s))
		this->m_CameraController.moveY(-0.03f);
	if (SF::Input::IsKeyPressed(SF::KeyCode::SFK_a))
		this->m_CameraController.moveX(-0.03f);
	if (SF::Input::IsKeyPressed(SF::KeyCode::SFK_d))
		this->m_CameraController.moveX(0.03f);

	SF::Renderer::beginScene(this->m_CameraController.getCamera());
	SF::Renderer::drawQuad(glm::vec2(0.0f, 0.0f), glm::vec2(0.5f, 0.5f), 45.0f, glm::vec4(0.2f, 0.4f, 0.2f, 1.0f));
	SF::Renderer::drawQuad(glm::vec2(1.0f, 2.0f), glm::vec2(0.2f, 1.5f), -10.0f, glm::vec4(0.8f, 0.4f, 0.2f, 1.0f));
	SF::Renderer::drawQuad(glm::vec2(-1.0f, 1.4f), glm::vec2(0.4f, 0.75f), 65.0f, glm::vec4(0.1f, 0.4f, 0.8f, 1.0f));
	SF::Renderer::endScene();
	
}

void Sandbox2D::onAttach() {


}

void Sandbox2D::onDetach() {


}

void Sandbox2D::onImGuiRender() {


}