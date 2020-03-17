#include "sfpch.h"
#include "application.h"
namespace SF {
	Application::Application() {

		this->m_ApplicationWindow = new Window(1024, 768, "SNOWFLAKE", 100, 100, SDL_WINDOW_RESIZABLE | SDL_WINDOW_FOREIGN);
		this->m_ApplicationWindow->setEventCallback(BIND_EVENT_FN(onEvent));

	}
	void Application::onEvent(Event& e) {

		for (auto it = this->m_LayerStack.end(); it != this->m_LayerStack.begin(); )
		{

			(*--it)->onEvent(e);
			if (e.m_Handled)
				break;

		}

	}

	bool Application::windowShouldClose()
	{
		return this->m_ApplicationWindow->shouldClose();
	}

	void Application::pushLayer(Layer* layer) {

		this->m_LayerStack.pushLayer(layer);

	}

	void Application::pushOverLay(Layer* layer) {

		this->m_LayerStack.pushOverlay(layer);

	}

	void Application::update() {

		for each (Layer * layer in this->m_LayerStack)
			layer->onUpdate();

		this->updateWindow();

	}

	void Application::updateWindow() {

		this->m_ApplicationWindow->update();

	}
}