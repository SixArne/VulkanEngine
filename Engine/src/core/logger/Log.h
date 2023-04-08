#ifndef LOG_H
#define LOG_H

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"

class Log
{
public:
    static void Init();

    inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger;  }
    inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger;  }

private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ClientLogger;
};

/************************************************************************/
/* Core logger macros													 */
/************************************************************************/
#define F_LOG_CORE_TRACE(...)		::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define F_LOG_CORE_INFO(...)		::Log::GetCoreLogger()->info(__VA_ARGS__)
#define F_LOG_CORE_DEBUG(...)		::Log::GetCoreLogger()->debug(__VA_ARGS__)
#define F_LOG_CORE_WARN(...)		::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define F_LOG_CORE_ERROR(...)		::Log::GetCoreLogger()->error(__VA_ARGS__)

/************************************************************************/
/* Client logger macros													 */
/************************************************************************/
#define F_LOG_TRACE(...)		::Log::GetClientLogger()->trace(__VA_ARGS__)
#define F_LOG_INFO(...)			::Log::GetClientLogger()->info(__VA_ARGS__)
#define F_LOG_DEBUG(...)		::Log::GetClientLogger()->debug(__VA_ARGS__)
#define F_LOG_WARN(...)			::Log::GetClientLogger()->warn(__VA_ARGS__)
#define F_LOG_ERROR(...)		::Log::GetClientLogger()->error(__VA_ARGS)

#endif