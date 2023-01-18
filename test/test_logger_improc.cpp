#include <gtest/gtest.h>

#include <improc/corecv/logger_improc.hpp>

TEST(LoggerCoreCv,TestLoggerLogging) {
    EXPECT_NE(improc::ImageProcLogger::get()->data(),nullptr);
    IMPROC_CORECV_LOGGER_TRACE("Test {} {}",1,2);
    IMPROC_CORECV_LOGGER_DEBUG("Test {} {}",2,3);
    IMPROC_CORECV_LOGGER_INFO ("Test {} {}",3,4);
    IMPROC_CORECV_LOGGER_ERROR("Test {} {}",4,5);
    IMPROC_CORECV_LOGGER_WARN ("Test {} {}",5,6);
    IMPROC_CORECV_LOGGER_CRITICAL("Test {} {}",6,7);
}
