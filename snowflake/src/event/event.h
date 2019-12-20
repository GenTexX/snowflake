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
		WindowEventCategory = BIT(0),
		InputEventCategory = BIT(1),
		KeyboardEventCategory = BIT(2),
		MouseEventCategory = BIT(3),
		
		ApplicationEventCategory = BIT(8)

	};

	struct Event
	{

		bool m_Handled;

		virtual EventType getEventType() const = 0;
		virtual EventCategory getEventCategory() const = 0;
		
		virtual std::string toString() const { return "Event"; }

		bool isInCategory(EventCategory category) const { return (this->getEventCategory() & category) == category; }

	};

}

#define EVENT_TYPE(type) static SF::EventType getStaticEventType(){ return SF::EventType::type; } \
						 virtual SF::EventType getEventType() const override { return getStaticEventType(); }

#define EVENT_CATEGORY(category) static SF::EventCategory getStaticEventCategory(){ return SF::EventCategory::category; } \
								 virtual SF::EventCategory getEventCategory() const override { return getStaticEventCategory(); }