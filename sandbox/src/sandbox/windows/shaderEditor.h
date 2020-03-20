#pragma once

#include "snowflake/imgui/imGuiWindow.h"
#include "snowflake/renderer/shader.h"
#include <string>
#include <imgui.h>

class ShaderEditorWindow : public SF::ImGuiWindow{

private:
	SF::Shader* m_Shader;
	std::string m_Source;

public:
	ShaderEditorWindow(SF::Shader* shader, const char* title = "Shader Editor") : SF::ImGuiWindow(title), m_Shader(shader) {}
	~ShaderEditorWindow() {}

	virtual void onRender() override;
	virtual void onAttach() override;
	virtual void onDetach() override;


};