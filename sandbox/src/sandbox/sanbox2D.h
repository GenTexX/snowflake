#pragma once
#include "snowflake.h"

class Sandbox2D : SF::Layer {

private:
	SF::OrthographicCameraController m_CameraController;

public:
	Sandbox2D();
	~Sandbox2D();

	void onEvent(SF::Event& event);
	void onUpdate();
	void onAttach();
	void onDetach();
	void onImGuiRender();

};