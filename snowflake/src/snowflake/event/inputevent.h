#pragma once
#include <sstream>
#include "event.h"
#include "keycode.h"
namespace SF {


	struct KeyboardEvent : Event
	{

		KeyCode m_KeyCode;

		EVENT_CATEGORY(KeyboardEventCategory | InputEventCategory)

	};

	struct KeyPressedEvent : KeyboardEvent {

		KeyPressedEvent(KeyCode kcode) { this->m_KeyCode = kcode; }

		std::string toString() const override {

			std::stringstream ss;

			ss << "KeyPressed\tKeyCode: " << this->m_KeyCode;

			return ss.str();

		}

		EVENT_TYPE(KeyPressed)

	};

	struct KeyReleasedEvent : KeyboardEvent {

		KeyReleasedEvent(KeyCode kcode) { this->m_KeyCode = kcode; }

		std::string toString() const override {

			std::stringstream ss;

			ss << "KeyReleased\tKeyCode: " << this->m_KeyCode;

			return ss.str();

		}

		EVENT_TYPE(KeyReleased)

	};

	struct KeyTypedEvent : Event{

		char* m_Text;

		KeyTypedEvent(char* text) { this->m_Text = text; }

		std::string toString() const override {

			std::stringstream ss;

			ss << "KeyTyped\tText: " << this->m_Text;

			return ss.str();

		}

		EVENT_CATEGORY(KeyboardEventCategory | InputEventCategory)
		EVENT_TYPE(KeyTyped)

	};

	struct MouseEvent : Event
	{

		std::string toString() const override {

			std::stringstream ss;

			ss << "MouseEvent";

			return ss.str();

		}

		EVENT_CATEGORY(InputEventCategory | MouseEventCategory)

	};

	struct MouseButtonEvent : MouseEvent {

		Uint8 m_Button;

		std::string toString() const override {

			std::stringstream ss;

			ss << "MouseButtonEvent";

			return ss.str();

		}

	};

	struct MouseButtonDown : MouseButtonEvent {


		MouseButtonDown(Uint8 btn) { m_Button = btn; }

		std::string toString() const override {

			std::stringstream ss;

			ss << "MouseButtonDown\tButton: " << (int)this->m_Button;

			return ss.str();

		}


		EVENT_TYPE(MouseButtonPressed)

	};

	struct MouseButtonUp : MouseButtonEvent {


		MouseButtonUp(Uint8 btn) { m_Button = btn; }

		std::string toString() const override {

			std::stringstream ss;

			ss << "MouseButtonUp\tButton: " << (int)this->m_Button;

			return ss.str();

		}


		EVENT_TYPE(MouseButtonReleased)

	};

	struct MouseMovedEvent : MouseEvent {

		int m_MousePosX, m_MousePosY;

		MouseMovedEvent(const int& x, const int& y) : m_MousePosX(x), m_MousePosY(y) {}

		std::string toString() const override {

			std::stringstream ss;

			ss << "MouseMoved: " << this->m_MousePosX << ", " << this->m_MousePosY;

			return ss.str();

		}

		EVENT_TYPE(MouseMoved)

	};

	struct MouseScrolledEvent : MouseEvent {

		int m_Scroll;

		MouseScrolledEvent(const int& scroll) : m_Scroll(scroll) {}

		std::string toString() const override {

			std::stringstream ss;

			ss << "MouseScrolled: " << this->m_Scroll;

			return ss.str();

		}

		EVENT_TYPE(MouseScrolled)

	};


}