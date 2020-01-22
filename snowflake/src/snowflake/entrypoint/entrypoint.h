#pragma once

#ifdef SF_PLATFORM_WINDOWS

#include <GL/glew.h>
#include "snowflake/logging/log.h"
#include "snowflake/application/application.h"
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
	} else SF_CORE_TRACE("Initialized SDL!");

	SF::Application* app = getApplication();

	app->init();


	if (glewInit() != GLEW_OK)
		return 0;


	app->run();


	return 0;

}

#endif // SF_PLATFORM_WINDOWS