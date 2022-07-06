#include "sanbox2D.h"
#include "snowflake/input/input.h"
#include <fstream>
#include <iostream>

Sandbox2D::Sandbox2D() : m_CameraController() {

	this->m_QuadTexture = "res/cobble_blood.png";
	SF::Texture::create(m_QuadTexture);

	SF::OrthographicCameraController cameraController = SF::OrthographicCameraController();

	SF::Ref<SF::TexturedQuad> quad = SF::createRef<SF::TexturedQuad>(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), m_QuadTexture);
	SF::Ref<SF::ColoredQuad> coloredQuad = SF::createRef<SF::ColoredQuad>(glm::vec3(1.2, 1.2, 0), glm::vec3(1, 1, 1), glm::vec4(0.2, 0.4, 0.6, 1.0));
	
	SF::Ref<SF::RenderableObject> quadObject = SF::createRef<SF::RenderableObject>(quad);
	SF::Ref<SF::RenderableObject> coloredQuadObject = SF::createRef<SF::RenderableObject>(coloredQuad);
	SF::Ref<SF::CameraObject> cameraObject = SF::createRef<SF::CameraObject>(cameraController);

	m_Scene = SF::createRef<SF::Scene>();

	m_Scene->addObject(quadObject);
	m_Scene->addObject(coloredQuadObject);
	m_Scene->setCameraObject(cameraObject);

	
	try {
		std::ofstream ofs("res/test.sfscene");
		boost::archive::binary_oarchive oa(ofs);
		oa.template register_type<SF::ColoredQuad>();
		oa.template register_type<SF::TexturedQuad>();
		oa.template register_type<SF::CameraObject>();
		oa.template register_type<SF::RenderableObject>();
		oa << m_Scene;
	} catch (boost::archive::archive_exception e) {
		std::cout << e.what();
	}

	m_Scene = SF::createRef<SF::Scene>();
	try {
		{
			std::ifstream ifs("res/test.sfscene");
			boost::archive::binary_iarchive ia(ifs);
			ia.template register_type<SF::ColoredQuad>();
			ia.template register_type<SF::TexturedQuad>();
			ia.template register_type<SF::CameraObject>();
			ia.template register_type<SF::RenderableObject>();
			ia >> m_Scene;
		}
	} catch (boost::archive::archive_exception e) {
		std::cout << e.what() << std::endl;
	}

	
	

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