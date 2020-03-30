#include "sfpch.h"
#include "input.h"
#include <SDL.h>


namespace SF {

	std::unique_ptr<Input> Input::s_Instance = Input::create();

	std::unique_ptr<Input> Input::create() {
		return std::make_unique<WindowsInput>();
	}

	bool WindowsInput::isKeyPressedImpl(KeyCode keycode)
	{

		const uint8_t* state = SDL_GetKeyboardState(NULL);
		return state[keycode];

	}

	std::pair<float, float> WindowsInput::getMousePositionImpl()
	{

		int x, y;
		SDL_GetMouseState(&x, &y);
		return std::pair<float, float>((float)x, (float)y);
	}

	float WindowsInput::getMouseXImpl()
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		return (float) x;
	}

	float WindowsInput::getMouseYImpl()
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		return (float) y;
	}

}