#include "sanbox2D.h"
#include "snowflake/input/input.h"

Sandbox2D::Sandbox2D() : m_CameraController() {

	this->m_QuadTexture = SF::Texture::create("test_texture.png");

	SF::OrthographicCameraController cameraController = SF::OrthographicCameraController();

	SF::Ref<SF::TexturedQuad> quad = SF::createRef<SF::TexturedQuad>(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), m_QuadTexture);
	
	SF::Ref<SF::RenderableObject> quadObject = SF::createRef<SF::RenderableObject>(quad);
	SF::Ref<SF::CameraObject> cameraObject = SF::createRef<SF::CameraObject>(cameraController);

	m_Scene = SF::createRef<SF::Scene>();

	m_Scene->addObject(quadObject);
	m_Scene->addObject(cameraObject);
	m_Scene->setCameraObject(cameraObject);

}

Sandbox2D::~Sandbox2D() {


}

void Sandbox2D::onEvent(SF::Event& event) {


}

void Sandbox2D::onUpdate(float deltatime) {

	SF::Renderer::drawScene(m_Scene);
	
}

void Sandbox2D::onAttach() {


}

void Sandbox2D::onDetach() {


}

void Sandbox2D::onImGuiRender() {


}