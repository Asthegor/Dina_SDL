#pragma once

#pragma warning (push)
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#pragma warning (pop)

namespace Dina
{
	template class DINA_API std::shared_ptr<spdlog::logger>; // Pour supprimer les warning C4251

	class DINA_API Log
	{
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	};

}


// Core Log Macros
#define DINA_CORE_TRACE(...)    ::Dina::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define DINA_CORE_INFO(...)     ::Dina::Log::GetCoreLogger()->info(__VA_ARGS__)
#define DINA_CORE_WARN(...)     ::Dina::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define DINA_CORE_ERROR(...)    ::Dina::Log::GetCoreLogger()->error(__VA_ARGS__)
#define DINA_CORE_CRITICAL(...) ::Dina::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client Log Macros
#define DINA_TRACE(...)         ::Dina::Log::GetClientLogger()->trace(__VA_ARGS__)
#define DINA_INFO(...)          ::Dina::Log::GetClientLogger()->info(__VA_ARGS__)
#define DINA_WARN(...)          ::Dina::Log::GetClientLogger()->warn(__VA_ARGS__)
#define DINA_ERROR(...)         ::Dina::Log::GetClientLogger()->error(__VA_ARGS__)
#define DINA_CRITICAL(...)      ::Dina::Log::GetClientLogger()->critical(__VA_ARGS__)
