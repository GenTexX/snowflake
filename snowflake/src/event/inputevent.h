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


}