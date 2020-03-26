#include "shaderEditor.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstring>

void ShaderEditorWindow::onRender() {

	char buff[100000];
	strcpy_s(buff, 100000, this->m_Source.c_str());
	ImGui::Begin(this->m_Title);
	ImGui::InputTextMultiline("", buff, 100000, ImVec2(500.0f, 500.0f));
	ImGui::SameLine();
	if (ImGui::Button("Save + Compile", ImVec2(150.0f, 25.0f))) {

		std::ofstream myfile(this->m_Shader->getFilePath());
		if (myfile.is_open())
		{
			myfile << this->m_Source;
			myfile.close();
		}
		else std::cout << "Unable to open file";
		m_Shader->readFile();
		m_Shader->compile();
	}
	ImGui::End();

	this->m_Source = buff;

}

void ShaderEditorWindow::onAttach() {

	this->m_Source = this->m_Shader->readFile();

}

void ShaderEditorWindow::onDetach() {
}
