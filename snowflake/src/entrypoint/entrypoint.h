#pragma once
#include "logging/log.h"
#include "application/application.h"

#ifdef SF_PLATFORM_WINDOWS

extern SF::Application* getApplication();

int main(int argc, char* args[]) {

	SF::Log::init();
	SF_CORE_TRACE("Initialized Logger!");

	SF::Application* app = getApplication();

	app->init();

	app->run();


	return 0;

}

#endif // SF_PLATFORM_WINDOWS
