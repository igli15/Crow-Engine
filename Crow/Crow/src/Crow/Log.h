#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
namespace Crow
{
	class CROW_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return engineLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetApplicationLogger() { return applicationLogger; }

	private:

		static std::shared_ptr<spdlog::logger> engineLogger;
		static std::shared_ptr<spdlog::logger> applicationLogger;

	};

#define ENGINE_LOG_INFO(...) :: Crow::Log::GetEngineLogger()->info(__VA_ARGS__)
#define ENGINE_LOG_WARNING(...) :: Crow::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define ENGINE_LOG_ERROR(...) :: Crow::Log::GetEngineLogger()->error(__VA_ARGS__)
#define ENGINE_LOG(...) :: Crow::Log::GetEngineLogger()->trace(__VA_ARGS__)

#define APP_LOG_INFO(...) :: Crow::Log::GetApplicationLogger()->info(__VA_ARGS__)
#define APP_LOG_WARNING(...) :: Crow::Log::GetApplicationLogger()->warn(__VA_ARGS__)
#define APP_LOG_ERROR(...) :: Crow::Log::GetApplicationLogger()->error(__VA_ARGS__)
#define APP_LOG(...) :: Crow::Log::GetApplicationLogger()->trace(__VA_ARGS__)

}