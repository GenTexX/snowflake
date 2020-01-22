#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace SF {
	class Log
	{

	public:
		static void init();

		static std::shared_ptr<spdlog::logger> getCoreLogger();
		static std::shared_ptr<spdlog::logger> getClientLogger();

		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};

}

#define SF_CORE_TRACE(...) SF::Log::getCoreLogger()->trace(__VA_ARGS__)
#define SF_CORE_INFO(...) SF::Log::getCoreLogger()->info(__VA_ARGS__)
#define SF_CORE_WARN(...) SF::Log::getCoreLogger()->warn(__VA_ARGS__)
#define SF_CORE_ERROR(...) SF::Log::getCoreLogger()->error(__VA_ARGS__)
#define SF_CORE_CRITICAL(...) SF::Log::getCoreLogger()->critical(__VA_ARGS__)

#define SF_TRACE(...) SF::Log::getClientLogger()->trace(__VA_ARGS__)
#define SF_INFO(...) SF::Log::getClientLogger()->info(__VA_ARGS__)
#define SF_WARN(...) SF::Log::getClientLogger()->warn(__VA_ARGS__)
#define SF_ERROR(...) SF::Log::getClientLogger()->error(__VA_ARGS__)
#define SF_CRITICAL(...) SF::Log::getClientLogger()->critical(__VA_ARGS__)