#pragma once
#include "snowflake.h"

class StatWindow : public SF::ImGuiWindow {
public:
	StatWindow(const std::string& title) : SF::ImGuiWindow(title) {
		
		
	
	}
	~StatWindow() {}

	void onRender(const float deltatime) override {
	
		ImGui::Begin(m_Title.c_str());
		ImGui::Text("FPS: %.0f", (1/deltatime) * 1000.0f);
		ImGui::End();
	
	}
	void onDetach() override {}
	void onAttach() override {}

private:
	

};