#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Holt {

	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()   { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define HL_CORE_TRACE(...)    ::Holt::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HL_CORE_INFO(...)     ::Holt::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HL_CORE_WARN(...)     ::Holt::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HL_CORE_ERROR(...)    ::Holt::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HL_CORE_CRITICAL(...) ::Holt::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define HL_TRACE(...)         ::Holt::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HL_INFO(...)          ::Holt::Log::GetClientLogger()->info(__VA_ARGS__)
#define HL_WARN(...)          ::Holt::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HL_ERROR(...)         ::Holt::Log::GetClientLogger()->error(__VA_ARGS__)
#define HL_CRITICAL(...)      ::Holt::Log::GetClientLogger()->critical(__VA_ARGS__)
