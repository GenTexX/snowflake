#pragma once
#include "event.h"
#include <sstream>

namespace SF {

	struct WindowEvent : Event {

		std::string toString() const override {	return "WindowEvent"; }

		EVENT_CATEGORY(WindowEventCategory)

	};


	/* WINDOW EVENTS */
	struct WindowResizeEvent : WindowEvent {

		int m_Width, m_Height;

		WindowResizeEvent(const int& width, const int& height) : m_Width(width), m_Height(height) {};
		
		std::string toString() const override {

			std::stringstream ss;

			ss << "WindowEvent: resized: " << this->m_Width << "px, " << this->m_Height << "px";

			return ss.str();

		}

		EVENT_TYPE(WindowResized)

	};

	struct WindowMinimizeEvent : WindowEvent {

		WindowMinimizeEvent() = default;

		std::string toString() const override {

			std::stringstream ss;

			ss << "WindowEvent: minimized";

		}

		EVENT_TYPE(WindowMinimized)

	};

	struct WindowMaximizeEvent : WindowEvent {

		WindowMaximizeEvent() = default;

		std::string toString() const override {

			std::stringstream ss;

			ss << "WindowEvent: maximized";

		}

		EVENT_TYPE(WindowMaximized)

	};

	struct WindowRestoreEvent : WindowEvent {

		WindowRestoreEvent() = default;

		std::string toString() const override {

			std::stringstream ss;

			ss << "WindowEvent: restored";

		}

		EVENT_TYPE(WindowRestored)

	};

	struct WindowEnterEvent : WindowEvent {

		WindowEnterEvent() = default;

		std::string toString() const override {

			std::stringstream ss;

			ss << "WindowEvent: enter";

		}

		EVENT_TYPE(WindowEnter)

	};

	struct WindowLeaveEvent : WindowEvent {

		WindowLeaveEvent() = default;

		std::string toString() const override {

			std::stringstream ss;

			ss << "WindowEvent: leave";

		}

		EVENT_TYPE(WindowLeave)

	};

	struct WindowFocusGainEvent : WindowEvent {

		WindowFocusGainEvent() = default;

		std::string toString() const override {

			std::stringstream ss;

			ss << "WindowEvent: focus gained";

		}

		EVENT_TYPE(WindowFocusGained)

	};

	struct WindowFocusLoseEvent : WindowEvent {

		WindowFocusLoseEvent() = default;

		std::string toString() const override {

			std::stringstream ss;

			ss << "WindowEvent: focus lost";

		}

		EVENT_TYPE(WindowFocusLost)

	};

	struct WindowCloseEvent : WindowEvent {

		WindowCloseEvent() = default;

		std::string toString() const override {

			std::stringstream ss;

			ss << "WindowEvent: closed";

		}

		EVENT_TYPE(WindowClose)

	};

	struct WindowTakeFocusEvent : WindowEvent {

		WindowTakeFocusEvent() = default;

		std::string toString() const override {

			std::stringstream ss;

			ss << "WindowEvent: take focus";

		}

		EVENT_TYPE(WindowTakeFocus)

	};

	struct WindowHitTestEvent : WindowEvent {

		WindowHitTestEvent() = default;

		std::string toString() const override {

			std::stringstream ss;

			ss << "WindowEvent: hit test";

		}

		EVENT_TYPE(WindowHitTest)

	};

}