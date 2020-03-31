#include "sfpch.h"
#include "application.h"

#include "snowflake/imgui/imGuiLayer.h"
#include "snowflake/platform/platform.h"

namespace SF {

	Application* Application::s_Instance = nullptr;

	Application::Application() {

		/* Application is a Singleton -- check foe existing instance */
		SF_ASSERT(!(this->s_Instance), "Multiple Applications. Application already exists!");

		s_Instance = this;

	}
	Application::~Application() {

		//SDL_SHUTDOWN
		SDL_GL_DeleteContext(this->m_ApplicationWindow->getContext());
		SDL_DestroyWindow(this->m_ApplicationWindow->getSDL_Window());
		SDL_Quit();

		delete this->m_ApplicationWindow;

	}
	void Application::onEvent(Event& e) {

		for (auto it = this->m_LayerStack.end(); it != this->m_LayerStack.begin(); )
		{

			(*--it)->onEvent(e);
			if (e.m_Handled)
				break;

		}

	}

	bool Application::isRunning()
	{
		return this->m_ApplicationWindow->shouldClose();
	}

	void Application::pushLayer(Layer* layer) {

		this->m_LayerStack.pushLayer(layer);
		layer->onAttach();

	}

	void Application::pushOverLay(Layer* layer) {

		this->m_LayerStack.pushOverlay(layer);
		layer->onAttach();

	}

	void Application::onUpdate() {

		float now = Platform::getTime();
		float deltatime = now - this->m_LastUpdate;

		for each (Layer * layer in this->m_LayerStack)
			layer->onUpdate(deltatime);

		this->updateWindow();

		this->m_LastUpdate = now;

	}

	void Application::init(){

		//create Window
		this->createWindow();


	}

	void Application::updateWindow() {

		this->m_ApplicationWindow->update();

	}
}