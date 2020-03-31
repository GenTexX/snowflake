#include "sanbox2D.h"
#include "snowflake/input/input.h"

Sandbox2D::Sandbox2D() : m_CameraController(){

	this->m_QuadTexture = SF::Texture::create("test_texture.png");

}

Sandbox2D::~Sandbox2D() {


}

void Sandbox2D::onEvent(SF::Event& event) {


}

void Sandbox2D::onUpdate() {

	if (SF::Input::isKeyPressed(SF::KeyCode::SFK_w))
		this->m_CameraController.moveY(0.03f);
	if (SF::Input::isKeyPressed(SF::KeyCode::SFK_s))
		this->m_CameraController.moveY(-0.03f);
	if (SF::Input::isKeyPressed(SF::KeyCode::SFK_a))
		this->m_CameraController.moveX(-0.03f);
	if (SF::Input::isKeyPressed(SF::KeyCode::SFK_d))
		this->m_CameraController.moveX(0.03f);

	SF::Renderer::beginScene(this->m_CameraController.getCamera());
	

	bool colortoggle = false;
	for (size_t i = 0; i < 27; i++) {
		for (size_t j = 0; j < 21; j++) {
			if (colortoggle) {
				SF::Renderer::drawQuad(glm::vec2(-3.9 + 0.3f * i, -2.9 + j * 0.3f), glm::vec2(0.3f, 0.3f), 0.0f, glm::vec4(0.6f, 0.6f, 0.6f, 1.0f));
			}
			else {
				SF::Renderer::drawQuad(glm::vec2(-3.9 + 0.3f * i, -2.9 + j * 0.3f), glm::vec2(0.3f, 0.3f), 0.0f, glm::vec4(0.9f, 0.9f, 0.9f, 1.0f));
			}
			colortoggle = !colortoggle;
		}
	}

	SF::Renderer::drawQuad(glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), 00.0f, this->m_QuadTexture);
	SF::Renderer::endScene();
	
}

void Sandbox2D::onAttach() {


}

void Sandbox2D::onDetach() {


}

void Sandbox2D::onImGuiRender() {


}