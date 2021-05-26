#include "Log.h"

namespace Crow
{
	std::shared_ptr<spdlog::logger> Log::engineLogger;
	std::shared_ptr<spdlog::logger> Log::applicationLogger;


	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		engineLogger = spdlog::stdout_color_mt("CROW");
		engineLogger->set_level(spdlog::level::trace);

		applicationLogger = spdlog::stdout_color_mt("APP");
		applicationLogger->set_level(spdlog::level::trace);
	}

}