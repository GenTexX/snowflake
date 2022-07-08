#pragma once

namespace SF {

	class ImGuiWindow
	{

	protected:
		std::string m_Title;
		bool m_Open = true;

	public:
		ImGuiWindow(const std::string& title = "ImGui Window") : m_Title(title) {}
		~ImGuiWindow() {};

		virtual void onRender(const float deltatime) = 0;
		virtual void onAttach() = 0;
		virtual void onDetach() = 0;

	};

}