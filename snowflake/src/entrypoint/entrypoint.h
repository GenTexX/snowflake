#pragma once

#ifdef SF_PLATFORM_WINDOWS


#include "logging/log.h"
#include "application/application.h"
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

extern SF::Application* getApplication();

int main(int argc, char* args[]) {

	SF::Log::init();
	SF_CORE_TRACE("Initialized Logger!");

	//initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {

		SF_CORE_ERROR("SDL initialization failed. Error: {}", SDL_GetError());
		return -1;
	} 
	SF_CORE_TRACE("Initialized SDL!");

	SF::Application* app = getApplication();

	app->init();

	if (glewInit() != GLEW_OK) {
		SF_CORE_ERROR("GLEW initialization failed.");
		return -1;
	}
	SF_CORE_TRACE("GLEW initialization succeeded.");

	app->run();


	return 0;

}

#endif // SF_PLATFORM_WINDOWS
