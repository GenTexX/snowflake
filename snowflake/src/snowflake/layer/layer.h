#pragma once
#include "snowflake/event/event.h"
#include "snowflake/time/timestep.h"

namespace SF {

	class Layer {

	protected:
		std::string m_Name;

	public:
		Layer(const std::string& name = "unnamed_layer") : m_Name(name) {};
		virtual ~Layer() = default;

		virtual void onAttach() = 0;
		virtual void onDetach() = 0;
		virtual void onUpdate() = 0;
		virtual void onImGuiRender() = 0;
		virtual void onEvent(Event& event) = 0;

		const std::string& getName() const { return this->m_Name; }

	};

}