#pragma once
#include <snowflake/event/keycode.h>
#include <memory>

namespace SF {

	class Input {

	private:
		static std::unique_ptr<Input> s_Instance;

	protected:
		
		virtual bool isKeyPressedImpl(KeyCode keycode) { return false; };
		virtual std::pair<float, float> getMousePositionImpl() { return std::pair<float, float>(0.0f, 0.0f); }
		virtual float getMouseXImpl() = 0;
		virtual float getMouseYImpl() = 0;

	public:
		Input() = default;

		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		inline static bool IsKeyPressed(KeyCode keycode) { return s_Instance->isKeyPressedImpl(keycode); }
		inline static std::pair<float, float> getMousePosition() { return s_Instance->getMousePositionImpl(); }
		inline static float getMouseX() { return s_Instance->getMouseXImpl(); }
		inline static float getMouseY() { return s_Instance->getMouseYImpl(); }

		static std::unique_ptr<Input> create();

	};

	class WindowsInput : public Input {
		
	protected:
		virtual bool isKeyPressedImpl(KeyCode keycode) override;
		virtual std::pair<float, float> getMousePositionImpl() override;
		virtual float getMouseXImpl() override;
		virtual float getMouseYImpl() override;

	};

}