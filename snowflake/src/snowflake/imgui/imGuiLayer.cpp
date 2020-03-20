#include "sfpch.h"
#include "imGuiLayer.h"

#include "snowflake/application/application.h"

#include <SDL.h>
#include <SDL_syswm.h>

namespace SF {

	ImGuiLayer* ImGuiLayer::s_Instance = nullptr;
	SDL_Cursor* ImGuiLayer::s_MouseCursors[ImGuiMouseCursor_COUNT] = {};

	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {
	
		SF_ASSERT(!s_Instance, "ImGuiLayer already exists! Singleton!");
		s_Instance = this;
	
	}

	ImGuiLayer::~ImGuiLayer() {

		//IMGUI_SHUTDOWN
		ImGui_ImplOpenGL3_Shutdown();
		this->shutdown();
		ImGui::DestroyContext();

	}

	void ImGuiLayer::onAttach() {

		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();

		//BackendFlags
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports; 

		//ConfigFlags
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;          
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		/* Windows will not merge with main Context */
		io.ConfigViewportsNoAutoMerge = true;

		ImGui::StyleColorsLight();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		io.KeyMap[ImGuiKey_Tab] = SFK_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = SFK_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = SFK_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = SFK_UP;
		io.KeyMap[ImGuiKey_DownArrow] = SFK_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = SFK_PAGEUP;
		io.KeyMap[ImGuiKey_PageDown] = SFK_PAGEDOWN;
		io.KeyMap[ImGuiKey_Home] = SFK_HOME;
		io.KeyMap[ImGuiKey_End] = SFK_END;
		io.KeyMap[ImGuiKey_Insert] = SFK_INSERT;
		io.KeyMap[ImGuiKey_Delete] = SFK_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = SFK_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = SFK_SPACE;
		io.KeyMap[ImGuiKey_Enter] = SFK_RETURN;
		io.KeyMap[ImGuiKey_Escape] = SFK_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] = SFK_RETURN2;
		io.KeyMap[ImGuiKey_A] = SFK_a;
		io.KeyMap[ImGuiKey_C] = SFK_c;
		io.KeyMap[ImGuiKey_V] = SFK_v;
		io.KeyMap[ImGuiKey_X] = SFK_x;
		io.KeyMap[ImGuiKey_Y] = SFK_y;
		io.KeyMap[ImGuiKey_Z] = SFK_z;

		s_MouseCursors[ImGuiMouseCursor_Arrow] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
		s_MouseCursors[ImGuiMouseCursor_TextInput] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
		s_MouseCursors[ImGuiMouseCursor_ResizeAll] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL);
		s_MouseCursors[ImGuiMouseCursor_ResizeNS] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENS);
		s_MouseCursors[ImGuiMouseCursor_ResizeEW] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE);
		s_MouseCursors[ImGuiMouseCursor_ResizeNESW] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENESW);
		s_MouseCursors[ImGuiMouseCursor_ResizeNWSE] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENWSE);
		s_MouseCursors[ImGuiMouseCursor_Hand] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
		s_MouseCursors[ImGuiMouseCursor_NotAllowed] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NO);

		// Our mouse update function expect PlatformHandle to be filled for the main viewport
		ImGuiViewport* main_viewport = ImGui::GetMainViewport();
		main_viewport->PlatformHandle = (void*)(Application::getInstance().getWindow()->getSDL_Window());

#if defined(SF_PLATFORM_WINDOWS)
		SDL_SysWMinfo info;
		SDL_VERSION(&info.version);
		if (SDL_GetWindowWMInfo((Application::getInstance().getWindow()->getSDL_Window()), &info))
			main_viewport->PlatformHandleRaw = info.info.win.window;
#endif

		this->updateMonitors();

		if ((io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) && (io.BackendFlags & ImGuiBackendFlags_PlatformHasViewports)) {


			// Register platform interface (will be coupled with a renderer interface)
			ImGuiPlatformIO& platform_io = ImGui::GetPlatformIO();
			platform_io.Platform_CreateWindow = imGuiCreateWindow;
			platform_io.Platform_DestroyWindow = imGuiDestroyWindow;
			platform_io.Platform_ShowWindow = imGuiShowWindow;
			platform_io.Platform_SetWindowPos = imGuiSetWindowPos;
			platform_io.Platform_GetWindowPos = imGuiGetWindowPos;
			platform_io.Platform_SetWindowSize = imGuiSetWindowSize;
			platform_io.Platform_GetWindowSize = imGuiGetWindowSize;
			platform_io.Platform_SetWindowFocus = imGuiSetWindowFocus;
			platform_io.Platform_GetWindowFocus = imGuiGetWindowFocus;
			platform_io.Platform_GetWindowMinimized = imGuiGetWindowMinimized;
			platform_io.Platform_SetWindowTitle = imGuiSetWindowTitle;
			platform_io.Platform_RenderWindow = imGuiRenderWindow;
			platform_io.Platform_SwapBuffers = imGuiSwapBuffers;
#if SDL_HAS_WINDOW_ALPHA
			platform_io.Platform_SetWindowAlpha = imGuiSetWindowAlpha;
#endif

			// SDL2 by default doesn't pass mouse clicks to the application when the click focused a window. This is getting in the way of our interactions and we disable that behavior.
#if SDL_HAS_MOUSE_FOCUS_CLICKTHROUGH
			SDL_SetHint(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, "1");
#endif

			// Register main window handle (which is owned by the main application, not by us)
			// This is mostly for simplicity and consistency, so that our code (e.g. mouse handling etc.) can use same logic for main and secondary viewports.
			ImGuiViewport* main_viewport = ImGui::GetMainViewport();
			ImGuiViewportDataSDL2* data = IM_NEW(ImGuiViewportDataSDL2)();
			data->Window = (Application::getInstance().getWindow()->getSDL_Window());
			data->WindowID = SDL_GetWindowID((Application::getInstance().getWindow()->getSDL_Window()));
			data->WindowOwned = false;
			data->GLContext = (Application::getInstance().getWindow()->getContext());
			main_viewport->PlatformUserData = data;
			main_viewport->PlatformHandle = data->Window;

		}

		io.DisplaySize = ImVec2(
			(float)(Application::getInstance().getWindow()->getWidth()),
			(float)(Application::getInstance().getWindow()->getHeight())
		);

		ImGui_ImplOpenGL3_Init("#version 410");

	}

	void ImGuiLayer::onDetach() {



	}

	void ImGuiLayer::onEvent(Event& e) {

		EventDispatcher dispatcher(e);
		dispatcher.dispatch<MouseButtonDown>(BIND_EVENT_FN(ImGuiLayer::mouseButtonDown));
		dispatcher.dispatch<MouseButtonUp>(BIND_EVENT_FN(ImGuiLayer::mouseButtonUp));
		dispatcher.dispatch<MouseMovedEvent>(BIND_EVENT_FN(ImGuiLayer::mouseMoved));
		dispatcher.dispatch<MouseScrolledEvent>(BIND_EVENT_FN(ImGuiLayer::mouseScrolled));
		dispatcher.dispatch<KeyPressedEvent>(BIND_EVENT_FN(ImGuiLayer::keyDown));
		dispatcher.dispatch<KeyReleasedEvent>(BIND_EVENT_FN(ImGuiLayer::keyReleased));
		dispatcher.dispatch<KeyTypedEvent>(BIND_EVENT_FN(ImGuiLayer::keyTyped));
		dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FN(ImGuiLayer::windowResized));
		dispatcher.dispatch<WindowMovedEvent>(BIND_EVENT_FN(ImGuiLayer::windowMoved));
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(ImGuiLayer::windowClosed));

	}

	void ImGuiLayer::onUpdate() {


		ImGuiIO& io = ImGui::GetIO();
		SF_ASSERT(io.Fonts->IsBuilt(), "Font atlas not Built!");


		static Uint64 frequency = SDL_GetPerformanceFrequency();
		Uint64 current_time = SDL_GetPerformanceCounter();
		io.DeltaTime = m_Time > 0 ? (float)((double)(current_time - m_Time) / frequency) : (float)(1.0f / 60.0f);
		m_Time = current_time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();



		/*  DRAW IMGUI  */
		for each (auto window in this->m_Windows)
		{
			window->onRender();
		}

		this->updateCursor();

		ImGui::Render();
		glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
			SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
		}



	}

	void ImGuiLayer::addWindow(ImGuiWindow* window) {

		this->m_Windows.push_back(window);
		window->onAttach();

	}

	void ImGuiLayer::removeWindow(ImGuiWindow* window) {

		window->onDetach();
		auto it = std::find(this->m_Windows.begin(), this->m_Windows.end(), window);
		this->m_Windows.erase(it);

	}

	bool ImGuiLayer::mouseButtonDown(MouseButtonDown& e) {

		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.m_Button - 1] = true;
		return io.WantCaptureMouse;

	}

	bool ImGuiLayer::mouseButtonUp(MouseButtonUp& e) {


		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.m_Button - 1] = false;

		return io.WantCaptureMouse;


	}

	bool ImGuiLayer::mouseMoved(MouseMovedEvent& e) {

		ImGuiIO& io = ImGui::GetIO();

		int mouse_x_global, mouse_y_global;
		SDL_GetGlobalMouseState(&mouse_x_global, &mouse_y_global);

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			// Multi-viewport mode: mouse position in OS absolute coordinates (io.MousePos is (0,0) when the mouse is on the upper-left of the primary monitor)
			if (SDL_Window* focused_window = SDL_GetKeyboardFocus())
				if (ImGui::FindViewportByPlatformHandle((void*)focused_window) != NULL)
					io.MousePos = ImVec2((float)mouse_x_global, (float)mouse_y_global);
		}
		else {

			io.MousePos = ImVec2((float)e.m_MousePosX, (float)e.m_MousePosY);


		}

		return io.WantCaptureMouse;

	}

	bool ImGuiLayer::mouseScrolled(MouseScrolledEvent& e) {

		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheel += e.m_Scroll;

		return io.WantCaptureMouse;

	}

	bool ImGuiLayer::windowResized(WindowResizeEvent& e) {

		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)e.m_Width, (float)e.m_Height);

		if (ImGuiViewport* viewport = ImGui::FindViewportByPlatformHandle((void*)e.m_WindowID))
		{
			viewport->PlatformRequestResize = true;
		}

		return false;

	}

	bool ImGuiLayer::windowMoved(WindowMovedEvent& e)
	{
		if (ImGuiViewport* viewport = ImGui::FindViewportByPlatformHandle((void*)e.m_WindowID))
		{
			viewport->PlatformRequestMove = true;
		}

		return false;
	}

	bool ImGuiLayer::windowClosed(WindowCloseEvent& e)
	{
		if (ImGuiViewport* viewport = ImGui::FindViewportByPlatformHandle((void*)e.m_WindowID))
		{
			viewport->PlatformRequestClose = true;
		}

		return false;
	}

	bool ImGuiLayer::keyDown(KeyPressedEvent& e) {

		ImGuiIO& io = ImGui::GetIO();
		if (e.m_KeyCode <= 512)
			io.KeysDown[e.m_KeyCode] = true;
		else
			SF_CORE_WARN("Unkown Keycode: ", e.m_KeyCode);

		return io.WantCaptureKeyboard;

	}

	bool ImGuiLayer::keyReleased(KeyReleasedEvent& e) {

		ImGuiIO& io = ImGui::GetIO();
		if (e.m_KeyCode <= 512)
			io.KeysDown[e.m_KeyCode] = false;


		return io.WantCaptureKeyboard;

	}

	bool ImGuiLayer::keyTyped(KeyTypedEvent& e) {

		ImGuiIO& io = ImGui::GetIO();
		io.AddInputCharactersUTF8(e.m_Text);

		return io.WantCaptureKeyboard;

	}

	void ImGuiLayer::shutdown()	{

		// Destroy SDL mouse cursors
		for (ImGuiMouseCursor cursor_n = 0; cursor_n < ImGuiMouseCursor_COUNT; cursor_n++)
			SDL_FreeCursor(s_MouseCursors[cursor_n]);
		memset(s_MouseCursors, 0, sizeof(s_MouseCursors));

	}

	void ImGuiLayer::imGuiCreateWindow(ImGuiViewport* viewport) {


		ImGuiViewportDataSDL2* data = IM_NEW(ImGuiViewportDataSDL2)();
		viewport->PlatformUserData = data;

		ImGuiViewport* main_viewport = ImGui::GetMainViewport();
		ImGuiViewportDataSDL2* main_viewport_data = (ImGuiViewportDataSDL2*)main_viewport->PlatformUserData;

		// Share GL resources with main context
		bool use_opengl = (main_viewport_data->GLContext != NULL);
		SDL_GLContext backup_context = NULL;
		if (use_opengl)
		{
			backup_context = SDL_GL_GetCurrentContext();
			SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);
			SDL_GL_MakeCurrent(main_viewport_data->Window, main_viewport_data->GLContext);
		}

		Uint32 sdl_flags = 0;
		sdl_flags |= use_opengl ? SDL_WINDOW_OPENGL : 0;
		sdl_flags |= SDL_GetWindowFlags(Application::getInstance().getWindow()->getSDL_Window()) & SDL_WINDOW_ALLOW_HIGHDPI;
		sdl_flags |= SDL_WINDOW_HIDDEN;
		sdl_flags |= (viewport->Flags & ImGuiViewportFlags_NoDecoration) ? SDL_WINDOW_BORDERLESS : 0;
		sdl_flags |= (viewport->Flags & ImGuiViewportFlags_NoDecoration) ? 0 : SDL_WINDOW_RESIZABLE;
#if !defined(SF_PLATFORM_WINDOWS)
		// See SDL hack in ImGui_ImplSDL2_ShowWindow().
		sdl_flags |= (viewport->Flags & ImGuiViewportFlags_NoTaskBarIcon) ? SDL_WINDOW_SKIP_TASKBAR : 0;
#endif
#if SDL_HAS_ALWAYS_ON_TOP
		sdl_flags |= (viewport->Flags & ImGuiViewportFlags_TopMost) ? SDL_WINDOW_ALWAYS_ON_TOP : 0;
#endif
		data->Window = SDL_CreateWindow("No Title Yet", (int)viewport->Pos.x, (int)viewport->Pos.y, (int)viewport->Size.x, (int)viewport->Size.y, sdl_flags);
		data->WindowOwned = true;
		if (use_opengl)
		{
			data->GLContext = SDL_GL_CreateContext(data->Window);
			SDL_GL_SetSwapInterval(0);
		}
		if (use_opengl && backup_context)
			SDL_GL_MakeCurrent(data->Window, backup_context);

		viewport->PlatformHandle = (void*)data->Window;
#if defined(SF_PLATFORM_WINDOWS)
		SDL_SysWMinfo info;
		SDL_VERSION(&info.version);
		if (SDL_GetWindowWMInfo(data->Window, &info))
			viewport->PlatformHandleRaw = info.info.win.window;
#endif
	}

	void ImGuiLayer::imGuiDestroyWindow(ImGuiViewport* viewport) {
	
		if (ImGuiViewportDataSDL2* data = (ImGuiViewportDataSDL2*)viewport->PlatformUserData)
		{
			if (data->GLContext && data->WindowOwned)
				SDL_GL_DeleteContext(data->GLContext);
			if (data->Window && data->WindowOwned)
				SDL_DestroyWindow(data->Window);
			data->GLContext = NULL;
			data->Window = NULL;
			IM_DELETE(data);
		}
		viewport->PlatformUserData = viewport->PlatformHandle = NULL;
	
	}

	void ImGuiLayer::imGuiShowWindow(ImGuiViewport* viewport) {


		ImGuiViewportDataSDL2* data = (ImGuiViewportDataSDL2*)viewport->PlatformUserData;

#if defined(SF_PLATFORM_WINDOWS)

		HWND hwnd = (HWND)viewport->PlatformHandleRaw;

		// SDL hack: Hide icon from task bar
		// Note: SDL 2.0.6+ has a SDL_WINDOW_SKIP_TASKBAR flag which is supported under Windows but the way it create the window breaks our seamless transition.
		if (viewport->Flags & ImGuiViewportFlags_NoTaskBarIcon)
		{
			LONG ex_style = ::GetWindowLong(hwnd, GWL_EXSTYLE);
			ex_style &= ~WS_EX_APPWINDOW;
			ex_style |= WS_EX_TOOLWINDOW;
			::SetWindowLong(hwnd, GWL_EXSTYLE, ex_style);
		}

		// SDL hack: SDL always activate/focus windows :/
		if (viewport->Flags & ImGuiViewportFlags_NoFocusOnAppearing)
		{
			::ShowWindow(hwnd, SW_SHOWNA);
			return;
		}
#endif

		SDL_ShowWindow(data->Window);

	}

	ImVec2 ImGuiLayer::imGuiGetWindowPos(ImGuiViewport* viewport)
	{
		ImGuiViewportDataSDL2* data = (ImGuiViewportDataSDL2*)viewport->PlatformUserData;
		int x = 0, y = 0;
		SDL_GetWindowPosition(data->Window, &x, &y);
		return ImVec2((float)x, (float)y);
	}

	void ImGuiLayer::imGuiSetWindowPos(ImGuiViewport* viewport, ImVec2 pos) {

		ImGuiViewportDataSDL2* data = (ImGuiViewportDataSDL2*)viewport->PlatformUserData;
		SDL_SetWindowPosition(data->Window, (int)pos.x, (int)pos.y);

	}

	ImVec2 ImGuiLayer::imGuiGetWindowSize(ImGuiViewport* viewport) {

		ImGuiViewportDataSDL2* data = (ImGuiViewportDataSDL2*)viewport->PlatformUserData;
		int w = 0, h = 0;
		SDL_GetWindowSize(data->Window, &w, &h);
		return ImVec2((float)w, (float)h);

	}

	void ImGuiLayer::imGuiSetWindowSize(ImGuiViewport* viewport, ImVec2 size) {

		ImGuiViewportDataSDL2* data = (ImGuiViewportDataSDL2*)viewport->PlatformUserData;
		SDL_SetWindowSize(data->Window, (int)size.x, (int)size.y);

	}

	void ImGuiLayer::imGuiSetWindowTitle(ImGuiViewport* viewport, const char* title) {

		ImGuiViewportDataSDL2* data = (ImGuiViewportDataSDL2*)viewport->PlatformUserData;
		SDL_SetWindowTitle(data->Window, title);

	}
#if SDL_HAS_WINDOW_ALPHA

	void ImGuiLayer::imGuiSetWindowAlpha(ImGuiViewport* viewport, float alpha) {
	
		ImGuiViewportDataSDL2* data = (ImGuiViewportDataSDL2*)viewport->PlatformUserData;
		SDL_SetWindowOpacity(data->Window, alpha);
	
	}

#endif

	void ImGuiLayer::imGuiSetWindowFocus(ImGuiViewport* viewport) {

		ImGuiViewportDataSDL2* data = (ImGuiViewportDataSDL2*)viewport->PlatformUserData;
		SDL_RaiseWindow(data->Window);

	}

	bool ImGuiLayer::imGuiGetWindowFocus(ImGuiViewport* viewport)
	{
		ImGuiViewportDataSDL2* data = (ImGuiViewportDataSDL2*)viewport->PlatformUserData;
		return (SDL_GetWindowFlags(data->Window) & SDL_WINDOW_INPUT_FOCUS) != 0;
	}

	bool ImGuiLayer::imGuiGetWindowMinimized(ImGuiViewport* viewport)
	{
		ImGuiViewportDataSDL2* data = (ImGuiViewportDataSDL2*)viewport->PlatformUserData;
		return (SDL_GetWindowFlags(data->Window) & SDL_WINDOW_MINIMIZED) != 0;
	}

	void ImGuiLayer::imGuiRenderWindow(ImGuiViewport* viewport, void*) {

		ImGuiViewportDataSDL2* data = (ImGuiViewportDataSDL2*)viewport->PlatformUserData;
		if (data->GLContext)
			SDL_GL_MakeCurrent(data->Window, data->GLContext);

	}

	void ImGuiLayer::imGuiSwapBuffers(ImGuiViewport* viewport, void*) {

		ImGuiViewportDataSDL2* data = (ImGuiViewportDataSDL2*)viewport->PlatformUserData;
		if (data->GLContext)
		{
			SDL_GL_MakeCurrent(data->Window, data->GLContext);
			SDL_GL_SwapWindow(data->Window);
		}

	}



	void ImGuiLayer::updateCursor() {

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange)
			return;

		ImGuiMouseCursor imgui_cursor = ImGui::GetMouseCursor();
		if (io.MouseDrawCursor || imgui_cursor == ImGuiMouseCursor_None)
		{
			// Hide OS mouse cursor if imgui is drawing it or if it wants no cursor
			SDL_ShowCursor(SDL_FALSE);
		}
		else
		{
			// Show OS mouse cursor
			SDL_SetCursor(s_MouseCursors[imgui_cursor] ? s_MouseCursors[imgui_cursor] : s_MouseCursors[ImGuiMouseCursor_Arrow]);
			SDL_ShowCursor(SDL_TRUE);

		}

	}

	void ImGuiLayer::updateMonitors() {


		ImGuiPlatformIO& platform_io = ImGui::GetPlatformIO();
		platform_io.Monitors.resize(0);
		int display_count = SDL_GetNumVideoDisplays();
		for (int n = 0; n < display_count; n++)
		{
			// Warning: the validity of monitor DPI information on Windows depends on the application DPI awareness settings, which generally needs to be set in the manifest or at runtime.
			ImGuiPlatformMonitor monitor;
			SDL_Rect r;
			SDL_GetDisplayBounds(n, &r);
			monitor.MainPos = monitor.WorkPos = ImVec2((float)r.x, (float)r.y);
			monitor.MainSize = monitor.WorkSize = ImVec2((float)r.w, (float)r.h);
#if SDL_HAS_USABLE_DISPLAY_BOUNDS
			SDL_GetDisplayUsableBounds(n, &r);
			monitor.WorkPos = ImVec2((float)r.x, (float)r.y);
			monitor.WorkSize = ImVec2((float)r.w, (float)r.h);
#endif
#if SDL_HAS_PER_MONITOR_DPI
			float dpi = 0.0f;
			if (!SDL_GetDisplayDPI(n, &dpi, NULL, NULL))
				monitor.DpiScale = dpi / 96.0f;
#endif
			platform_io.Monitors.push_back(monitor);
		}

	}

}