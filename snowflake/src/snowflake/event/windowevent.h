#pragma once
#include "event.h"
#include <sstream>

namespace SF {

	struct WindowEvent : Event {

		uint8_t m_WindowID = 0;

		std::string toString() const override {	return "WindowEvent"; }

		EVENT_CATEGORY(WindowEventCategory)

	};


	/* WINDOW EVENTS */

	struct WindowShownEvent : public WindowEvent {

		WindowShownEvent(uint8_t id) { this->m_WindowID = id;  };

		std::string toString() const override {

			std::stringstream ss;

			ss << "WindowEvent: shown";

			return ss.str();

		}

		EVENT_TYPE(WindowShown)

	};

	struct WindowHiddenEvent : WindowEvent {

		WindowHiddenEvent(uint8_t id) { this->m_WindowID = id; };

		std::string toString() const override {

			std::stringstream ss;

			ss << "WindowEvent: hidden";

			return ss.str();

		}

		EVENT_TYPE(WindowHidden)

	};

	struct WindowExposedEvent : WindowEvent {

		WindowExposedEvent(uint8_t id) { this->m_WindowID = id; };

		std::string toString() const override {

			std::stringstream ss;

			ss << "WindowEvent: exposed";

			return ss.str();

		}

		EVENT_TYPE(WindowExposed)

	};

	struct WindowMovedEvent : WindowEvent {

		int m_PosX, m_PosY;

		WindowMovedEvent(const int& posx, const int& posy, uint8_t id) : m_PosX(posx), m_PosY(posy) { this->m_WindowID = id; };

		std::string toString() const override {

			std::stringstream ss;

			ss << "WindowEvent: moved: " << this->m_PosX << "px, " << this->m_PosY << "px";

			return ss.str();

		}

		EVENT_TYPE(WindowMoved)


	};

	struct WindowResizeEvent : WindowEvent {

		int m_Width, m_Height;

		WindowResizeEvent(const int& width, const int& height, uint8_t id) : m_Width(width), m_Height(height) { this->m_WindowID = id; };
		
		std::string toString() const override {

			std::stringstream ss;

			ss << "WindowEvent: resized: " << this->m_Width << "px, " << this->m_Height << "px";

			return ss.str();

		}

		EVENT_TYPE(WindowResized)

	};

	struct WindowMinimizeEvent : WindowEvent {

		WindowMinimizeEvent(uint8_t id) { this->m_WindowID = id; };

		std::string toString() const override {

			std::stringstream ss;

			ss << "WindowEvent: minimized";

			return ss.str();

		}

		EVENT_TYPE(WindowMinimized)

	};

	struct WindowMaximizeEvent : WindowEvent {

		WindowMaximizeEvent(uint8_t id) { this->m_WindowID = id; };

		std::string toString() const override {

			std::stringstream ss;

			ss << "WindowEvent: maximized";

			return ss.str();

		}

		EVENT_TYPE(WindowMaximized)

	};

	struct WindowRestoreEvent : WindowEvent {

		WindowRestoreEvent(uint8_t id) { this->m_WindowID = id; };

		std::string toString() const override {

			std::stringstream ss;

			ss << "WindowEvent: restored";

			return ss.str();

		}

		EVENT_TYPE(WindowRestored)

	};

	struct WindowEnterEvent : WindowEvent {

		WindowEnterEvent(uint8_t id) { this->m_WindowID = id; };

		std::string toString() const override {

			std::stringstream ss;

			ss << "WindowEvent: entered";

			return ss.str();

		}

		EVENT_TYPE(WindowEnter)

	};

	struct WindowLeaveEvent : WindowEvent {

		WindowLeaveEvent(uint8_t id) { this->m_WindowID = id; };

		std::string toString() const override {

			std::stringstream ss;

			ss << "WindowEvent: left";

			return ss.str();

		}

		EVENT_TYPE(WindowLeave)

	};

	struct WindowFocusGainEvent : WindowEvent {

		WindowFocusGainEvent(uint8_t id) { this->m_WindowID = id; };

		std::string toString() const override {

			std::stringstream ss;

			ss << "WindowEvent: focus gained";

			return ss.str();

		}

		EVENT_TYPE(WindowFocusGained)

	};

	struct WindowFocusLoseEvent : WindowEvent {

		WindowFocusLoseEvent(uint8_t id) { this->m_WindowID = id; };

		std::string toString() const override {

			std::stringstream ss;

			ss << "WindowEvent: focus lost";

			return ss.str();

		}

		EVENT_TYPE(WindowFocusLost)

	};

	struct WindowCloseEvent : WindowEvent {

		WindowCloseEvent(uint8_t id) { this->m_WindowID = id; };

		std::string toString() const override {

			std::stringstream ss;

			ss << "WindowEvent: closed";

			return ss.str();

		}

		EVENT_TYPE(WindowClose)

	};

	struct WindowTakeFocusEvent : WindowEvent {

		WindowTakeFocusEvent(uint8_t id) { this->m_WindowID = id; };

		std::string toString() const override {

			std::stringstream ss;

			ss << "WindowEvent: take focus";

			return ss.str();

		}

		EVENT_TYPE(WindowTakeFocus)

	};

	struct WindowHitTestEvent : WindowEvent {

		WindowHitTestEvent(uint8_t id) { this->m_WindowID = id; };

		std::string toString() const override {

			std::stringstream ss;

			ss << "WindowEvent: hit test";

			return ss.str();

		}

		EVENT_TYPE(WindowHitTest)

	};

}