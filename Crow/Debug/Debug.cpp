//
// Created by Igli milaqi on 06/02/2020.
//

#include "Debug.h"

std::shared_ptr<spdlog::logger> Debug::m_engineLogger;
std::shared_ptr<spdlog::logger> Debug::m_appLogger;

void Debug::Init()
{
    spdlog::set_pattern("%^[%T] %n: %v%$");

    m_engineLogger = spdlog::stdout_color_mt("Engine");
    m_engineLogger->set_level(spdlog::level::trace);

    m_appLogger = spdlog::stdout_color_mt("App");
    m_appLogger->set_level(spdlog::level::trace);

}


void Debug::Assert(bool assertion, const std::string& msg)
{
    assert(assertion && msg.data());
}
