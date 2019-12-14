#include "sfpch.h"
#include "window.h"

namespace SF {

	SDL_Event Window::s_Event;

	Window::Window(const int& width, const int& height, const char* title, const int& x, const int& y, Uint32 flags)
	{

		flags |= SDL_WINDOW_OPENGL;

		this->m_Window = SDL_CreateWindow(title, x, y, width, height, flags);
		SDL_PollEvent(&(Window::s_Event));
		SDL_AddEventWatch(this->handleEvent, this);

		this->m_Context = SDL_GL_CreateContext(this->m_Window);
		SDL_GL_MakeCurrent(this->m_Window, this->m_Context);

		SDL_GL_SetSwapInterval(1);

	}

	Window::~Window()
	{

		SDL_GL_DeleteContext(this->m_Context);

		SDL_DestroyWindow(this->m_Window);

	}

	void Window::update()
	{

		SDL_PollEvent(&(Window::s_Event));

		SDL_GL_SwapWindow(this->m_Window);

	}

	bool Window::shouldClose()
	{

		if (Window::s_Event.window.windowID == SDL_GetWindowID(this->m_Window))
			return Window::s_Event.window.event == SDL_WINDOWEVENT_CLOSE;
		
		return false;

	}


	/* GETTER */
	int Window::getWidth()
	{
		int w, h;

		SDL_GetWindowSize(this->m_Window, &w, &h);

		return w;
	}

	int Window::getHeight()
	{
		int w, h;

		SDL_GetWindowSize(this->m_Window, &w, &h);

		return h;
	}

	int Window::getMaxWidth()
	{
		int w, h;

		SDL_GetWindowMaximumSize(this->m_Window, &w, &h);

		return w;
	}

	int Window::getMaxHeight()
	{
		int w, h;

		SDL_GetWindowMaximumSize(this->m_Window, &w, &h);

		return h;
	}

	float Window::getOpacity()
	{
		float o;

		SDL_GetWindowOpacity(this->m_Window, &o);

		return o;
	}

	int Window::getPosX()
	{
		int x, y;

		SDL_GetWindowPosition(this->m_Window, &x, &y);

		return x;
	}

	int Window::getPosY()
	{
		int x, y;

		SDL_GetWindowPosition(this->m_Window, &x, &y);

		return y;
	}

	std::string Window::getTitle()
	{
		return SDL_GetWindowTitle(this->m_Window);
	}

	SDL_Window* Window::getSDL_Window()
	{
		return this->m_Window;
	}

	SDL_GLContext& Window::getContext()
	{
		return this->m_Context;
	}


	/* SETTER */
	void Window::setWidth(const int& w)
	{

		SDL_SetWindowSize(this->m_Window, w, this->getHeight());

	}

	void Window::setHeight(const int& h)
	{

		SDL_SetWindowSize(this->m_Window, this->getWidth(), h);

	}

	void Window::setMaxWidth(const int& w)
	{

		SDL_SetWindowMaximumSize(this->m_Window, w, this->getMaxHeight());

	}

	void Window::setMaxHeight(const int& h)
	{

		SDL_SetWindowMaximumSize(this->m_Window, this->getMaxWidth(), h);

	}

	void Window::setOpacity(const float& o)
	{

		SDL_SetWindowOpacity(this->m_Window, o);

	}

	void Window::setPosX(const int& x)
	{

		SDL_SetWindowPosition(this->m_Window, x, this->getPosY());

	}

	void Window::setPosY(const int& y)
	{

		SDL_SetWindowPosition(this->m_Window, this->getPosX(), y);

	}

	void Window::setTitle(const std::string& title)
	{

		SDL_SetWindowTitle(this->m_Window, title.c_str());

	}





	int Window::handleEvent(void* data, SDL_Event* event)
	{

		Window* w = (Window*)data;

		switch (event->type)
		{
		case SDL_WINDOWEVENT:
			switch (event->window.event) {
			case SDL_WINDOWEVENT_RESIZED:
				break;
			case SDL_WINDOWEVENT_MOVED:
				break;
			case SDL_WINDOWEVENT_MAXIMIZED:
				break;
			case SDL_WINDOWEVENT_MINIMIZED:
				break;
			case SDL_WINDOWEVENT_HIDDEN:
				break;
			case SDL_WINDOWEVENT_EXPOSED:
				break;
			case SDL_WINDOWEVENT_LEAVE:
				break;
			default:
				break;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			break;
		case SDL_MOUSEBUTTONUP:
			break;
		case SDL_MOUSEMOTION:
			break;
		case SDL_MOUSEWHEEL:
			break;
		case SDL_KEYDOWN:
			break;
		case SDL_KEYUP:
			break;
		default:
			break;
		}

		return 0;
	}

}
