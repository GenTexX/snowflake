#pragma once
#include <SDL.h>
#include "snowflake/event/event.h"

namespace SF {

	class Application
	{

	private:
	
	
	public:
		Application() {}
		virtual ~Application() {}

		virtual void onEvent(Event& e) {}

		virtual void init() {}
		virtual void run() {}

	};

}