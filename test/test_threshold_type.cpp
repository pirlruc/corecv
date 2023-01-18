#include <gtest/gtest.h>

#include <improc/corecv/structures/threshold_type.hpp>

TEST(ThresholdType,TestEmptyThresholdTypeConstructor) {
    improc::ThresholdType threshold {};
    EXPECT_EQ(threshold,improc::ThresholdType::Value::kOtsu);
}

TEST(ThresholdType,TestConstructorFromValue) {
    improc::ThresholdType threshold {improc::ThresholdType::Value::kBinary};
    EXPECT_EQ(threshold,improc::ThresholdType::Value::kBinary);
}

TEST(ThresholdType,TestConstructorFromLowerString) {
    improc::ThresholdType threshold_otsu {"otsu"};
    improc::ThresholdType threshold_binary {"binary"};
    EXPECT_EQ(threshold_otsu  ,improc::ThresholdType::Value::kOtsu);
    EXPECT_EQ(threshold_binary,improc::ThresholdType::Value::kBinary);
}

TEST(ThresholdType,TestConstructorFromUpperString) {
    improc::ThresholdType threshold_otsu {"OTSU"};
    improc::ThresholdType threshold_binary {"BINARY"};
    EXPECT_EQ(threshold_otsu  ,improc::ThresholdType::Value::kOtsu);
    EXPECT_EQ(threshold_binary,improc::ThresholdType::Value::kBinary);
}

TEST(ThresholdType,TestInvalidThresholdConstructor) {
    EXPECT_THROW(improc::ThresholdType threshold {"invalid"},std::out_of_range);
}

TEST(ThresholdType,TestConstructorFromClass) {
    EXPECT_EQ(improc::ThresholdType::kOtsu  ,improc::ThresholdType::Value::kOtsu);
    EXPECT_EQ(improc::ThresholdType::kBinary,improc::ThresholdType::Value::kBinary);
}

TEST(ThresholdType,TestToString) {
    improc::ThresholdType threshold_otsu   {"otsu"};
    improc::ThresholdType threshold_binary {"binary"};
    EXPECT_EQ(threshold_otsu.ToString()  ,"Otsu");
    EXPECT_EQ(threshold_binary.ToString(),"Binary");
}

TEST(ThresholdType,TestToOpenCV) {
    improc::ThresholdType threshold_otsu   {"otsu"};
    improc::ThresholdType threshold_binary {"binary"};
    EXPECT_EQ(threshold_otsu.ToOpenCV()  ,cv::THRESH_OTSU);
    EXPECT_EQ(threshold_binary.ToOpenCV(),cv::THRESH_BINARY);
}
