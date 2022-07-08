#include "sanbox2D.h"
#include "snowflake/input/input.h"


Sandbox2D::Sandbox2D() : m_CameraController() {
	
	m_Scene = SF::createRef<SF::Scene>("res/test.sfscene");
	this->m_QuadTexture = "res/cobble_blood.png";
	SF::Texture::create(m_QuadTexture);

	SF::OrthographicCameraController cameraController = SF::OrthographicCameraController();

	SF::Ref<SF::TexturedQuad> quad = SF::createRef<SF::TexturedQuad>(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), m_QuadTexture);
	SF::Ref<SF::ColoredQuad> coloredQuad = SF::createRef<SF::ColoredQuad>(glm::vec3(1.2, 1.2, 0), glm::vec3(1, 1, 1), glm::vec4(0.2, 0.4, 0.6, 1.0));
	
	SF::Ref<SF::RenderableObject> quadObject = SF::createRef<SF::RenderableObject>(quad);
	SF::Ref<SF::RenderableObject> coloredQuadObject = SF::createRef<SF::RenderableObject>(coloredQuad);
	SF::Ref<SF::CameraObject> cameraObject = SF::createRef<SF::CameraObject>(cameraController);

	glm::vec4 color1(0.7, 0.7, 0.7, 1.0);
	glm::vec4 color2(0.9, 0.9, 0.9, 1.0);
	bool c = false;
	for (size_t i = 0; i < 17; i++)
	{
		for (size_t j = 0; j < 13; j++)
		{
			SF::Ref<SF::ColoredQuad> coloredQuad1 = SF::createRef<SF::ColoredQuad>(glm::vec3(0.5 * i - 4, 0.5 * j - 3, 0), glm::vec3(0.49, 0.49, 1), c ? color1 : color2);
			SF::Ref<SF::RenderableObject> coloredQuadObject1 = SF::createRef<SF::RenderableObject>(coloredQuad1);
			m_Scene->addObject(coloredQuadObject1);
			c = !c;

		}
	}


	m_Scene->setCameraObject(cameraObject);
	
	m_Scene->save();

	//m_Scene->load();
	
	
	

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