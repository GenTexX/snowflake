#include "sfpch.h"
#include "log.h"

namespace SF {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::init()
	{

		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_CoreLogger = spdlog::stdout_color_mt("SNOWFLAKE");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APPLICATION");
		s_ClientLogger->set_level(spdlog::level::trace);


	}

	std::shared_ptr<spdlog::logger> Log::getCoreLogger()
	{
		return s_CoreLogger;
	}

	std::shared_ptr<spdlog::logger> Log::getClientLogger()
	{
		return s_ClientLogger;
	}

}