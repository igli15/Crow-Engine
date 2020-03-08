//
// Created by Igli milaqi on 06/02/2020.
//

#ifndef CROW_DEBUG_H
#define CROW_DEBUG_H


#include <string>
#include <iostream>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <memory>

class Debug {

public:
    static void Init();

    inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() {return m_engineLogger;};
    inline static std::shared_ptr<spdlog::logger>& GetAppLogger() {return m_appLogger;};

    static void Assert(bool assertion,const std::string&);

private:

    static std::shared_ptr<spdlog::logger> m_engineLogger;
    static std::shared_ptr<spdlog::logger> m_appLogger;

};

#define ENGINE_LOG_ERROR(...) Debug::GetEngineLogger()->error(__VA_ARGS__)
#define ENGINE_LOG_CRITICAL(...) Debug::GetEngineLogger()->critical(__VA_ARGS__)
#define ENGINE_LOG_WARNING(...) Debug::GetEngineLogger()->warn(__VA_ARGS__)
#define ENGINE_LOG(...) Debug::GetEngineLogger()->info(__VA_ARGS__)

#define APP_LOG_ERROR(...) Debug::GetAppLogger()->error(__VA_ARGS__)
#define APP_LOG_CRITICAL(...) Debug::GetAppLogger()->critical(__VA_ARGS__)
#define APP_LOG_WARNING(...) Debug::GetAppLogger()->warn(__VA_ARGS__)
#define APP_LOG(...) Debug::GetAppLogger()->info(__VA_ARGS__)

#endif //CROW_DEBUG_H
