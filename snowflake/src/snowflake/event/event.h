#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include <string>

namespace SF {

	enum class EventType {

		None = 0,
		
		/* WINDOW */
		WindowShown, WindowHidden, WindowExposed, WindowMoved,
		WindowResized, WindowMinimized, WindowMaximized, WindowRestored,
		WindowEnter, WindowLeave, WindowFocusGained, WindowFocusLost,
		WindowClose, WindowTakeFocus, WindowHitTest,

		/* KEYBOARD */
		KeyPressed, KeyReleased, KeyTyped,
	
		/* MOUSE */
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,

		/* APPLICATION */
		ApplicationTick, ApplicationRender, ApplicationUpdate

	};

	enum EventCategory {

		None = 0,
		WindowEventCategory = (1 << 0),
		InputEventCategory = (1 << 1),
		KeyboardEventCategory = (1 << 2),
		MouseEventCategory = (1 << 3),
		
		ApplicationEventCategory = (1<<8)

	};

	struct Event
	{

		bool m_Handled = false;

		virtual EventType getEventType() const = 0;
		virtual int getEventCategory() const = 0;
		
		virtual std::string toString() const { return "Event"; }

		bool isInCategory(EventCategory category) const { return (this->getEventCategory() & category) == category; }



	};

	class EventDispatcher {

	private:
		Event& m_Event;

	public:
		EventDispatcher(Event& e) : m_Event(e) {}
		~EventDispatcher() {}

		template<typename T, typename F>
		bool dispatch(const F& function) {

			if (this->m_Event.getEventType() == T::getStaticEventType()) {
			
				m_Event.m_Handled = function(static_cast<T&>(m_Event));
				return true;
			
			}

			return false;

		}

	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.toString();
	}

}

#define EVENT_TYPE(type) static SF::EventType getStaticEventType(){ return SF::EventType::type; } \
						 virtual SF::EventType getEventType() const override { return getStaticEventType(); }

#define EVENT_CATEGORY(category) virtual int getEventCategory() const override { return category; }