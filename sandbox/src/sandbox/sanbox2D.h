#pragma once
#include "snowflake.h"

class Sandbox2D : public SF::Layer {

private:
	SF::OrthographicCameraController m_CameraController;
	SF::Ref<SF::Texture> m_QuadTexture;
public:
	Sandbox2D();
	~Sandbox2D();

	void onEvent(SF::Event& event);
	void onUpdate();
	void onAttach();
	void onDetach();
	void onImGuiRender();

};