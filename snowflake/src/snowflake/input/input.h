#pragma once
#include <snowflake/event/keycode.h>
#include <memory>

namespace SF {

	class Input {

	private:
		static Input* s_Instance;

	protected:
		Input() = default;

		virtual bool IsKeyPressedImpl(KeyCode keycode) = 0;
		virtual std::pair<float, float> getMousePositionImpl() = 0;
		virtual float getMouseXImpl() = 0;
		virtual float getMouseYImpl() = 0;

	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		inline static bool IsKeyPressed(KeyCode keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		inline static std::pair<float, float> getMousePosition() { return s_Instance->getMousePositionImpl(); }
		inline static float getMouseX() { return s_Instance->getMouseXImpl();  }
		inline static float getMouseY() { return s_Instance->getMouseYImpl();  }

	};

}