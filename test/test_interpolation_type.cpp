#include <gtest/gtest.h>

#include <improc/corecv/structures/interpolation_type.hpp>

TEST(InterpolationType,TestEmptyInterpolationTypeConstructor) {
    improc::InterpolationType interpolation {};
    EXPECT_EQ(interpolation,improc::InterpolationType::Value::kLinear);
}

TEST(InterpolationType,TestConstructorFromValue) {
    improc::InterpolationType interpolation {improc::InterpolationType::Value::kCubic};
    EXPECT_EQ(interpolation,improc::InterpolationType::Value::kCubic);
}

TEST(InterpolationType,TestConstructorFromLowerString) {
    improc::InterpolationType interpolation_linear {"linear"};
    improc::InterpolationType interpolation_cubic  {"cubic"};
    improc::InterpolationType interpolation_nearest{"nearest"};
    EXPECT_EQ(interpolation_linear ,improc::InterpolationType::Value::kLinear);
    EXPECT_EQ(interpolation_cubic  ,improc::InterpolationType::Value::kCubic);
    EXPECT_EQ(interpolation_nearest,improc::InterpolationType::Value::kNearest);
}

TEST(InterpolationType,TestConstructorFromUpperString) {
    improc::InterpolationType interpolation_linear {"LINEAR"};
    improc::InterpolationType interpolation_cubic  {"CUBIC"};
    improc::InterpolationType interpolation_nearest{"NEAREST"};
    EXPECT_EQ(interpolation_linear ,improc::InterpolationType::Value::kLinear);
    EXPECT_EQ(interpolation_cubic  ,improc::InterpolationType::Value::kCubic);
    EXPECT_EQ(interpolation_nearest,improc::InterpolationType::Value::kNearest);
}

TEST(InterpolationType,TestInvalidInterpolationConstructor) {
    EXPECT_THROW(improc::InterpolationType interpolation {"invalid"},std::out_of_range);
}

TEST(InterpolationType,TestConstructorFromClass) {
    EXPECT_EQ(improc::InterpolationType::kLinear ,improc::InterpolationType::Value::kLinear);
    EXPECT_EQ(improc::InterpolationType::kCubic  ,improc::InterpolationType::Value::kCubic);
    EXPECT_EQ(improc::InterpolationType::kNearest,improc::InterpolationType::Value::kNearest);
}

TEST(InterpolationType,TestToString) {
    improc::InterpolationType interpolation_linear {"linear"};
    improc::InterpolationType interpolation_cubic  {"cubic"};
    improc::InterpolationType interpolation_nearest{"nearest"};
    EXPECT_EQ(interpolation_linear.ToString() ,"Linear");
    EXPECT_EQ(interpolation_cubic.ToString()  ,"Cubic");
    EXPECT_EQ(interpolation_nearest.ToString(),"Nearest");
}

TEST(InterpolationType,TestToOpenCV) {
    improc::InterpolationType interpolation_linear {"linear"};
    improc::InterpolationType interpolation_cubic  {"cubic"};
    improc::InterpolationType interpolation_nearest{"nearest"};
    EXPECT_EQ(interpolation_linear.ToOpenCV() ,cv::INTER_LINEAR);
    EXPECT_EQ(interpolation_cubic.ToOpenCV()  ,cv::INTER_CUBIC);
    EXPECT_EQ(interpolation_nearest.ToOpenCV(),cv::INTER_NEAREST);
}
