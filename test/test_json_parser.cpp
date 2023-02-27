#include <gtest/gtest.h>

#include <improc_corecv_test_config.hpp>

#include <improc/corecv/parsers/json_parser.hpp>
#include <improc/infrastructure/filesystem/file.hpp>

TEST(PointParser,TestParsing) {
    std::string json_filepath = std::string(IMPROC_CORECV_TEST_FOLDER) + "/test/data/point_parser.json";
    Json::Value json_content  = improc::JsonFile::Read(json_filepath);
    EXPECT_EQ(improc::json::ReadElement<cv::Point>(json_content["point-int"]),cv::Point(6,10));
    EXPECT_EQ(improc::json::ReadElement<cv::Point2d>(json_content["point-double"]),cv::Point2d(6.3,10.6));
}

TEST(PointParser,TestNoTopLeftX) {
    std::string json_filepath = std::string(IMPROC_CORECV_TEST_FOLDER) + "/test/data/point_parser.json";
    Json::Value json_content  = improc::JsonFile::Read(json_filepath);
    EXPECT_THROW(improc::json::ReadElement<cv::Point>(json_content["point-no-x"]),improc::json_error);
}

TEST(PointParser,TestNoTopLeftY) {
    std::string json_filepath = std::string(IMPROC_CORECV_TEST_FOLDER) + "/test/data/point_parser.json";
    Json::Value json_content  = improc::JsonFile::Read(json_filepath);
    EXPECT_THROW(improc::json::ReadElement<cv::Point>(json_content["point-no-y"]),improc::json_error);
}

TEST(SizeParser,TestParsing) {
    std::string json_filepath = std::string(IMPROC_CORECV_TEST_FOLDER) + "/test/data/size_parser.json";
    Json::Value json_content  = improc::JsonFile::Read(json_filepath);
    EXPECT_EQ(improc::json::ReadElement<cv::Size>(json_content["size-int"]),cv::Size(6,10));
    EXPECT_EQ(improc::json::ReadElement<cv::Size2d>(json_content["size-double"]),cv::Size2d(6.3,10.6));
}

TEST(SizeParser,TestNoPageWidth) {
    std::string json_filepath = std::string(IMPROC_CORECV_TEST_FOLDER) + "/test/data/size_parser.json";
    Json::Value json_content  = improc::JsonFile::Read(json_filepath);
    EXPECT_THROW(improc::json::ReadElement<cv::Size>(json_content["size-no-width"]),improc::json_error);
}

TEST(SizeParser,TestNoPageHeight) {
    std::string json_filepath = std::string(IMPROC_CORECV_TEST_FOLDER) + "/test/data/size_parser.json";
    Json::Value json_content  = improc::JsonFile::Read(json_filepath);
    EXPECT_THROW(improc::json::ReadElement<cv::Size>(json_content["size-no-height"]),improc::json_error);
}

TEST(PositiveSizeParser,TestInvalidWidth) {
    std::string json_filepath = std::string(IMPROC_CORECV_TEST_FOLDER) + "/test/data/size_parser.json";
    Json::Value json_content  = improc::JsonFile::Read(json_filepath);
    EXPECT_THROW(improc::json::ReadPositiveSize<cv::Size>(json_content["size-invalid-width"]),improc::value_error);
    EXPECT_THROW(improc::json::ReadPositiveSize<cv::Size2d>(json_content["size-invalid-width"]),improc::value_error);
}

TEST(PositiveSizeParser,TestInvalidHeight) {
    std::string json_filepath = std::string(IMPROC_CORECV_TEST_FOLDER) + "/test/data/size_parser.json";
    Json::Value json_content  = improc::JsonFile::Read(json_filepath);
    EXPECT_THROW(improc::json::ReadPositiveSize<cv::Size>(json_content["size-invalid-height"]),improc::value_error);
    EXPECT_THROW(improc::json::ReadPositiveSize<cv::Size2d>(json_content["size-invalid-height"]),improc::value_error);
}
