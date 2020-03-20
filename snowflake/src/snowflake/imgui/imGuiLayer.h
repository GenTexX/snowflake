#pragma once
#include "imGuiWindow.h"
#include "opengl/imgui/imGuiRenderer.h"
#include "snowflake/event/keycode.h"
#include "snowflake/event/event.h"
#include "snowflake/event/inputevent.h"
#include "snowflake/event/windowevent.h"
#include "snowflake/layer/layer.h"
#include "snowflake/core/core.h"

#define SDL_HAS_CAPTURE_AND_GLOBAL_MOUSE    SDL_VERSION_ATLEAST(2,0,4)
#define SDL_HAS_WINDOW_ALPHA                SDL_VERSION_ATLEAST(2,0,5)
#define SDL_HAS_ALWAYS_ON_TOP               SDL_VERSION_ATLEAST(2,0,5)
#define SDL_HAS_USABLE_DISPLAY_BOUNDS       SDL_VERSION_ATLEAST(2,0,5)
#define SDL_HAS_PER_MONITOR_DPI             SDL_VERSION_ATLEAST(2,0,4)
#define SDL_HAS_VULKAN                      SDL_VERSION_ATLEAST(2,0,6)
#define SDL_HAS_MOUSE_FOCUS_CLICKTHROUGH    SDL_VERSION_ATLEAST(2,0,5)

namespace SF {

	struct ImGuiViewportDataSDL2
	{
		SDL_Window* Window;
		Uint32          WindowID;
		bool            WindowOwned;
		SDL_GLContext   GLContext;

		ImGuiViewportDataSDL2() { Window = NULL; WindowID = 0; WindowOwned = false; GLContext = NULL; }
		~ImGuiViewportDataSDL2() { IM_ASSERT(Window == NULL && GLContext == NULL); }
	};

	class ImGuiLayer : public Layer {

	private:
		static ImGuiLayer* s_Instance;
		std::vector<ImGuiWindow*> m_Windows;

		uint64_t m_Time = 0;


		bool mouseButtonDown(MouseButtonDown& e);
		bool mouseButtonUp(MouseButtonUp& e);
		bool mouseMoved(MouseMovedEvent& e);
		bool mouseScrolled(MouseScrolledEvent& e);
		bool windowResized(WindowResizeEvent& e);
		bool windowMoved(WindowMovedEvent& e);
		bool windowClosed(WindowCloseEvent& e);
		bool keyDown(KeyPressedEvent& e);
		bool keyReleased(KeyReleasedEvent& e);
		bool keyTyped(KeyTypedEvent& e);

		void shutdown();

		static void imGuiCreateWindow(ImGuiViewport* viewport);
        static void imGuiDestroyWindow(ImGuiViewport* viewport);
        static void imGuiShowWindow(ImGuiViewport* viewport);
        static ImVec2 imGuiGetWindowPos(ImGuiViewport* viewport);
		static void imGuiSetWindowPos(ImGuiViewport* viewport, ImVec2 pos);
        static ImVec2 imGuiGetWindowSize(ImGuiViewport* viewport);
        static void imGuiSetWindowSize(ImGuiViewport* viewport, ImVec2 size);
        static void imGuiSetWindowTitle(ImGuiViewport* viewport, const char* title);


        static void imGuiSetWindowFocus(ImGuiViewport* viewport);
        static bool imGuiGetWindowFocus(ImGuiViewport* viewport);
        static bool imGuiGetWindowMinimized(ImGuiViewport* viewport);
        static void imGuiRenderWindow(ImGuiViewport* viewport, void*);
        static void imGuiSwapBuffers(ImGuiViewport* viewport, void*);

#if SDL_HAS_WINDOW_ALPHA
        static void imGuiSetWindowAlpha(ImGuiViewport* viewport, float alpha);
#endif
		
		void updateCursor();
		void updateMonitors();

		static SDL_Cursor* s_MouseCursors[ImGuiMouseCursor_COUNT];


	public:
		ImGuiLayer();
		~ImGuiLayer();

		void onAttach() override;
		void onDetach() override;

		void onEvent(Event& e) override;
		void onUpdate();

		void addWindow(ImGuiWindow* window);
		void removeWindow(ImGuiWindow* window);

		void onImGuiRender() override {}

	};

}