#include "sfpch.h"
#include "platformWindows.h"

namespace SF {

	PlatformWindows::PlatformWindows() {
		this->m_StartTime = std::chrono::high_resolution_clock::now();
	}

	float PlatformWindows::getTimeImpl() {

		auto now = std::chrono::high_resolution_clock::now();

		return std::chrono::duration_cast<std::chrono::microseconds>(now - this->m_StartTime).count() * 0.001;

	}

}