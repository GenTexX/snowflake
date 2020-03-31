#pragma once
#include "snowflake/platform/platform.h"

#include <chrono>

namespace SF {

	class PlatformWindows : public Platform {

	private:
		std::chrono::high_resolution_clock::time_point m_StartTime;

	public:
		PlatformWindows();
		virtual float getTimeImpl() override;

	};

}