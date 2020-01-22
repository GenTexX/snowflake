#pragma once

namespace SF {

	class Timestep {

	private:
		float m_Time;

	public:
		Timestep(const float& timestep = 0.0f) : m_Time(timestep) {}

		operator float() const { return this->m_Time; }

		float getSeconds() const { return this->m_Time; }
		float getMilliSeconds() const { return this->m_Time * 1000.0f; }

	};

}