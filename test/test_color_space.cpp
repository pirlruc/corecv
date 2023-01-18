#include <gtest/gtest.h>

#include <improc/corecv/structures/color_space.hpp>

TEST(ColorSpace,TestEmptyColorSpaceConstructor) {
    improc::ColorSpace color_space {};
    EXPECT_EQ(color_space,improc::ColorSpace::Value::kRGB);
}

TEST(ColorSpace,TestConstructorFromValue) {
    improc::ColorSpace color_space {improc::ColorSpace::Value::kRGBA};
    EXPECT_EQ(color_space,improc::ColorSpace::Value::kRGBA);
}

TEST(ColorSpace,TestConstructorFromLowerString) {
    improc::ColorSpace color_space_bgr {"bgr"};
    improc::ColorSpace color_space_rgb {"rgb"};
    improc::ColorSpace color_space_bgra{"bgra"};
    improc::ColorSpace color_space_rgba{"rgba"};
    improc::ColorSpace color_space_gray{"gray"};
    EXPECT_EQ(color_space_bgr ,improc::ColorSpace::Value::kBGR );
    EXPECT_EQ(color_space_rgb ,improc::ColorSpace::Value::kRGB );
    EXPECT_EQ(color_space_bgra,improc::ColorSpace::Value::kBGRA);
    EXPECT_EQ(color_space_rgba,improc::ColorSpace::Value::kRGBA);
    EXPECT_EQ(color_space_gray,improc::ColorSpace::Value::kGray);
}

TEST(ColorSpace,TestConstructorFromUpperString) {
    improc::ColorSpace color_space_bgr {"BGR"};
    improc::ColorSpace color_space_rgb {"RGB"};
    improc::ColorSpace color_space_bgra{"BGRA"};
    improc::ColorSpace color_space_rgba{"RGBA"};
    improc::ColorSpace color_space_gray{"GRAY"};
    EXPECT_EQ(color_space_bgr ,improc::ColorSpace::Value::kBGR );
    EXPECT_EQ(color_space_rgb ,improc::ColorSpace::Value::kRGB );
    EXPECT_EQ(color_space_bgra,improc::ColorSpace::Value::kBGRA);
    EXPECT_EQ(color_space_rgba,improc::ColorSpace::Value::kRGBA);
    EXPECT_EQ(color_space_gray,improc::ColorSpace::Value::kGray);
}

TEST(ColorSpace,TestInvalidStringConstructor) {
    EXPECT_THROW(improc::ColorSpace color_space {"invalid"},std::out_of_range);
}

TEST(ColorSpace,TestConstructorFromClass) {
    EXPECT_EQ(improc::ColorSpace::kBGR ,improc::ColorSpace::Value::kBGR);
    EXPECT_EQ(improc::ColorSpace::kRGB ,improc::ColorSpace::Value::kRGB);
    EXPECT_EQ(improc::ColorSpace::kBGRA,improc::ColorSpace::Value::kBGRA);
    EXPECT_EQ(improc::ColorSpace::kRGBA,improc::ColorSpace::Value::kRGBA);
    EXPECT_EQ(improc::ColorSpace::kGray,improc::ColorSpace::Value::kGray);
}

TEST(ColorSpace,TestToString) {
    improc::ColorSpace color_space_bgr {"bgr"};
    improc::ColorSpace color_space_rgb {"rgb"};
    improc::ColorSpace color_space_bgra{"bgra"};
    improc::ColorSpace color_space_rgba{"rgba"};
    improc::ColorSpace color_space_gray{"gray"};
    EXPECT_EQ(color_space_bgr.ToString() ,"BGR");
    EXPECT_EQ(color_space_rgb.ToString() ,"RGB");
    EXPECT_EQ(color_space_bgra.ToString(),"BGRA");
    EXPECT_EQ(color_space_rgba.ToString(),"RGBA");
    EXPECT_EQ(color_space_gray.ToString(),"Gray");
}

TEST(ColorSpace,TestNumberChannels) {
    improc::ColorSpace color_space_bgr {"bgr"};
    improc::ColorSpace color_space_rgb {"rgb"};
    improc::ColorSpace color_space_bgra{"bgra"};
    improc::ColorSpace color_space_rgba{"rgba"};
    improc::ColorSpace color_space_gray{"gray"};
    EXPECT_EQ(color_space_bgr.GetNumberChannels() ,3);
    EXPECT_EQ(color_space_rgb.GetNumberChannels() ,3);
    EXPECT_EQ(color_space_bgra.GetNumberChannels(),4);
    EXPECT_EQ(color_space_rgba.GetNumberChannels(),4);
    EXPECT_EQ(color_space_gray.GetNumberChannels(),1);
}

TEST(ColorSpace,TestGetColorConversionCodeBGR) {
    improc::ColorSpace color_space_bgr {"bgr"};
    improc::ColorSpace color_space_rgb {"rgb"};
    improc::ColorSpace color_space_bgra{"bgra"};
    improc::ColorSpace color_space_rgba{"rgba"};
    improc::ColorSpace color_space_gray{"gray"};
    EXPECT_THROW(color_space_bgr.GetColorConversionCode(color_space_bgr),improc::not_supported_color_conversion);
    EXPECT_EQ(color_space_bgr.GetColorConversionCode(color_space_rgb) ,cv::COLOR_BGR2RGB);
    EXPECT_EQ(color_space_bgr.GetColorConversionCode(color_space_bgra),cv::COLOR_BGR2BGRA);
    EXPECT_EQ(color_space_bgr.GetColorConversionCode(color_space_rgba),cv::COLOR_BGR2RGBA);
    EXPECT_EQ(color_space_bgr.GetColorConversionCode(color_space_gray),cv::COLOR_BGR2GRAY);
}

TEST(ColorSpace,TestGetColorConversionCodeRGB) {
    improc::ColorSpace color_space_bgr {"bgr"};
    improc::ColorSpace color_space_rgb {"rgb"};
    improc::ColorSpace color_space_bgra{"bgra"};
    improc::ColorSpace color_space_rgba{"rgba"};
    improc::ColorSpace color_space_gray{"gray"};
    EXPECT_EQ(color_space_rgb.GetColorConversionCode(color_space_bgr) ,cv::COLOR_RGB2BGR);
    EXPECT_THROW(color_space_rgb.GetColorConversionCode(color_space_rgb),improc::not_supported_color_conversion);
    EXPECT_EQ(color_space_rgb.GetColorConversionCode(color_space_bgra),cv::COLOR_RGB2BGRA);
    EXPECT_EQ(color_space_rgb.GetColorConversionCode(color_space_rgba),cv::COLOR_RGB2RGBA);
    EXPECT_EQ(color_space_rgb.GetColorConversionCode(color_space_gray),cv::COLOR_RGB2GRAY);
}

TEST(ColorSpace,TestGetColorConversionCodeBGRA) {
    improc::ColorSpace color_space_bgr {"bgr"};
    improc::ColorSpace color_space_rgb {"rgb"};
    improc::ColorSpace color_space_bgra{"bgra"};
    improc::ColorSpace color_space_rgba{"rgba"};
    improc::ColorSpace color_space_gray{"gray"};
    EXPECT_EQ(color_space_bgra.GetColorConversionCode(color_space_bgr) ,cv::COLOR_BGRA2BGR);
    EXPECT_EQ(color_space_bgra.GetColorConversionCode(color_space_rgb) ,cv::COLOR_BGRA2RGB);
    EXPECT_THROW(color_space_bgra.GetColorConversionCode(color_space_bgra),improc::not_supported_color_conversion);
    EXPECT_EQ(color_space_bgra.GetColorConversionCode(color_space_rgba),cv::COLOR_BGRA2RGBA);
    EXPECT_EQ(color_space_bgra.GetColorConversionCode(color_space_gray),cv::COLOR_BGRA2GRAY);
}

TEST(ColorSpace,TestGetColorConversionCodeRGBA) {
    improc::ColorSpace color_space_bgr {"bgr"};
    improc::ColorSpace color_space_rgb {"rgb"};
    improc::ColorSpace color_space_bgra{"bgra"};
    improc::ColorSpace color_space_rgba{"rgba"};
    improc::ColorSpace color_space_gray{"gray"};
    EXPECT_EQ(color_space_rgba.GetColorConversionCode(color_space_bgr) ,cv::COLOR_RGBA2BGR);
    EXPECT_EQ(color_space_rgba.GetColorConversionCode(color_space_rgb) ,cv::COLOR_RGBA2RGB);
    EXPECT_EQ(color_space_rgba.GetColorConversionCode(color_space_bgra),cv::COLOR_RGBA2BGRA);
    EXPECT_THROW(color_space_rgba.GetColorConversionCode(color_space_rgba),improc::not_supported_color_conversion);
    EXPECT_EQ(color_space_rgba.GetColorConversionCode(color_space_gray),cv::COLOR_RGBA2GRAY);
}

TEST(ColorSpace,TestGetColorConversionCodeGray) {
    improc::ColorSpace color_space_bgr {"bgr"};
    improc::ColorSpace color_space_rgb {"rgb"};
    improc::ColorSpace color_space_bgra{"bgra"};
    improc::ColorSpace color_space_rgba{"rgba"};
    improc::ColorSpace color_space_gray{"gray"};
    EXPECT_EQ(color_space_gray.GetColorConversionCode(color_space_bgr) ,cv::COLOR_GRAY2BGR);
    EXPECT_EQ(color_space_gray.GetColorConversionCode(color_space_rgb) ,cv::COLOR_GRAY2RGB);
    EXPECT_EQ(color_space_gray.GetColorConversionCode(color_space_bgra),cv::COLOR_GRAY2BGRA);
    EXPECT_EQ(color_space_gray.GetColorConversionCode(color_space_rgba),cv::COLOR_GRAY2RGBA);
    EXPECT_THROW(color_space_gray.GetColorConversionCode(color_space_gray),improc::not_supported_color_conversion);
}
