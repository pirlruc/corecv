#ifndef IMPROC_CORECV_LOGGER_IMPROC_HPP
#define IMPROC_CORECV_LOGGER_IMPROC_HPP

#include <improc/improc_defs.hpp>
#include <improc/infrastructure/logging/logger_singleton.hpp>

namespace improc 
{
    /**
     * @brief Logger used for image processing library
     * 
     */
    class IMPROC_API ImageProcLogger final : public improc::LoggerSingleton<ImageProcLogger>
    {
        friend std::shared_ptr<ImageProcLogger> LoggerSingleton::get(const std::string& logger_name);
        private:
            ImageProcLogger(std::shared_ptr<spdlog::logger>&& logger) : LoggerSingleton(std::move(logger)) {}

        public:
            ImageProcLogger(ImageProcLogger&  that)       = delete;
            ImageProcLogger(ImageProcLogger&& that)       = delete;
            void operator=(const ImageProcLogger&  that)  = delete;
            void operator=(const ImageProcLogger&& that)  = delete;
    };
}

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_TRACE
#    define IMPROC_CORECV_LOGGER_TRACE(...) IMPROC_LOGGER_TRACE(improc::ImageProcLogger::get(), __VA_ARGS__)
#else
#    define IMPROC_CORECV_LOGGER_TRACE(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_DEBUG
#    define IMPROC_CORECV_LOGGER_DEBUG(...) IMPROC_LOGGER_DEBUG(improc::ImageProcLogger::get(), __VA_ARGS__)
#else
#    define IMPROC_CORECV_LOGGER_DEBUG(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_INFO
#    define IMPROC_CORECV_LOGGER_INFO(...) IMPROC_LOGGER_INFO(improc::ImageProcLogger::get(), __VA_ARGS__)
#else
#    define IMPROC_CORECV_LOGGER_INFO(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_WARN
#    define IMPROC_CORECV_LOGGER_WARN(...) IMPROC_LOGGER_WARN(improc::ImageProcLogger::get(), __VA_ARGS__)
#else
#    define IMPROC_CORECV_LOGGER_WARN(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_ERROR
#    define IMPROC_CORECV_LOGGER_ERROR(...) IMPROC_LOGGER_ERROR(improc::ImageProcLogger::get(), __VA_ARGS__)
#else
#    define IMPROC_CORECV_LOGGER_ERROR(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_CRITICAL
#    define IMPROC_CORECV_LOGGER_CRITICAL(...) IMPROC_LOGGER_CRITICAL(improc::ImageProcLogger::get(), __VA_ARGS__)
#else
#    define IMPROC_CORECV_LOGGER_CRITICAL(...) (void)0
#endif

#endif