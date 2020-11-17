#pragma once

#include "openGameEngine3D/Core/Base.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

/*
	Hazel Engine
	License : Apache 2.0
*/

namespace openGameEngine3D
{
	class Log
	{
	public:
		static void Init ();
		
		static Ref<spdlog::logger>& GetCoreLogger ()
		{
			return s_CoreLogger;
		}
		static Ref<spdlog::logger>& GetClientLogger ()
		{
			return s_ClientLogger;
		}

	private:
		
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
		
	};
}

// Core log macros
#define OGE_CORE_TRACE(...)    ::openGameEngine3D::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define OGE_CORE_INFO(...)     ::openGameEngine3D::Log::GetCoreLogger()->info(__VA_ARGS__)
#define OGE_CORE_WARN(...)     ::openGameEngine3D::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define OGE_CORE_ERROR(...)    ::openGameEngine3D::Log::GetCoreLogger()->error(__VA_ARGS__)
#define OGE_CORE_CRITICAL(...) ::openGameEngine3D::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define OGE_TRACE(...)         ::openGameEngine3D::Log::GetClientLogger()->trace(__VA_ARGS__)
#define OGE_INFO(...)          ::openGameEngine3D::Log::GetClientLogger()->info(__VA_ARGS__)
#define OGE_WARN(...)          ::openGameEngine3D::Log::GetClientLogger()->warn(__VA_ARGS__)
#define OGE_ERROR(...)         ::openGameEngine3D::Log::GetClientLogger()->error(__VA_ARGS__)
#define OGE_CRITICAL(...)	   ::openGameEngine3D::Log::GetClientLogger()->critical(__VA_ARGS__) 
