#pragma once
#include <SDL.h>
#include "snowflake/core/core.h"
#include "snowflake/window/window.h"
#include "snowflake/event/event.h"
#include "snowflake/layer/layer.h"
#include "snowflake/layer/layerStack.h"
#include <imgui.h>

namespace SF {


	class Application
	{

	protected:
		Window *m_ApplicationWindow;
		LayerStack m_LayerStack;
	
	private:
		static Application* s_Instance;	//the only Application instance

		virtual void createWindow() = 0;

		void updateWindow();

	public:
		Application();
		virtual ~Application();

		virtual void onEvent(Event& e);

		inline static Application& getInstance() { return *(s_Instance); }
		inline Window* getWindow() const { return this->m_ApplicationWindow; }

		bool isRunning();		//check if Application is still Running
		
		void pushLayer(Layer* layer);	//push layer to layerstack
		void pushOverLay(Layer* layer);	//push overlay to layerstack

		void onUpdate();				//needs to be called every frame

		virtual void init();		//is called when application is started
		virtual void run() = 0;			//is called after

	};

}