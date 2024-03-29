#pragma once
#include "snowflake.h"

class Sandbox2D : public SF::Layer {

private:
	SF::OrthographicCameraController m_CameraController;
	std::string m_QuadTexture;
	SF::Ref<SF::Scene> m_Scene;

public:
	Sandbox2D();
	~Sandbox2D();

	void onEvent(SF::Event& event);
	void onUpdate(float deltatime);
	void onAttach();
	void onDetach();
	void onImGuiRender();

};