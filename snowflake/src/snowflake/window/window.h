#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include <snowflake/logging/log.h>
#include <snowflake/event/windowevent.h>
#include <snowflake/event/inputevent.h>

namespace SF {

	class Window
	{

	private:
		SDL_Window* m_Window;
		SDL_GLContext m_Context;

		static int handleEvent(void* data, SDL_Event* event);

		using EventCallback = std::function<void(Event&)>;

		EventCallback eventCallback;

	public:
		static SDL_Event s_Event;

		Window(const int& width = 1024,
			const int& height = 768,
			const char* title = "SNOWFLAKE",
			const int& x = SDL_WINDOWPOS_CENTERED,
			const int& y = SDL_WINDOWPOS_CENTERED,
			Uint32 flags = 0);
		~Window();

		void update();

		bool shouldClose();

		int getWidth();
		int getHeight();
		int getMaxWidth();
		int getMaxHeight();
		float getOpacity();
		int getPosX();
		int getPosY();
		std::string getTitle();
		SDL_Window* getSDL_Window();
		SDL_GLContext& getContext();

		void setWidth(const int& w);
		void setHeight(const int& h);
		void setMaxWidth(const int& w);
		void setMaxHeight(const int& h);
		void setOpacity(const float& o);
		void setPosX(const int& x);
		void setPosY(const int& y);
		void setTitle(const std::string& title);

		void setEventCallback(const EventCallback& callback);

	};

}