#include "sanbox2D.h"

Sandbox2D::Sandbox2D() : m_CameraController(){
}

Sandbox2D::~Sandbox2D()
{
}

void Sandbox2D::onEvent(SF::Event& event) {

	switch (event.getEventType())
	{
	case SF::EventType::KeyPressed:

		this->m_CameraController.moveX(0.1f);

		break;
	default:
		break;
	}

}

void Sandbox2D::onUpdate()
{
}

void Sandbox2D::onAttach()
{
}

void Sandbox2D::onDetach()
{
}

void Sandbox2D::onImGuiRender()
{
}
