#pragma once
#include <SDL.h>
#include "snowflake/window/window.h"
#include "snowflake/event/event.h"
#include "snowflake/layer/layer.h"
#include "snowflake/layer/layerStack.h"

namespace SF {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	class Application
	{

	private:
		Window* m_ApplicationWindow;
		LayerStack m_LayerStack;
	

		void updateWindow();

	public:
		Application();
		virtual ~Application() {}

		virtual void onEvent(Event& e);

		bool windowShouldClose();

		void pushLayer(Layer* layer);
		void pushOverLay(Layer* layer);


		void update();

		virtual void init() {}
		virtual void run() {}

	};

}