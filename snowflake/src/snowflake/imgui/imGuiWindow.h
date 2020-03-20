#pragma once

namespace SF {

	class ImGuiWindow
	{

	protected:
		const char* m_Title;
		bool m_Open = true;

	public:
		ImGuiWindow(const char* title = "ImGui Window") : m_Title(title) {}
		~ImGuiWindow() {};

		virtual void onRender() = 0;
		virtual void onAttach() = 0;
		virtual void onDetach() = 0;

	};

}