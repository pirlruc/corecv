#include <gtest/gtest.h>

#include <improc/corecv/structures/image_format.hpp>

TEST(ImageFormat,TestEmptyImageFormatConstructor) {
    improc::ImageFormat image_format {};
    EXPECT_EQ(image_format,improc::ImageFormat::Value::kPNG);
}

TEST(ImageFormat,TestConstructorFromValue) {
    improc::ImageFormat image_format {improc::ImageFormat::Value::kJPEG};
    EXPECT_EQ(image_format,improc::ImageFormat::Value::kJPEG);
}

TEST(ImageFormat,TestConstructorFromLowerString) {
    improc::ImageFormat image_format_png      {"png"};
    improc::ImageFormat image_format_jpeg     {"jpeg"};
    improc::ImageFormat image_format_jpeg2000 {"jpeg2000"};
    EXPECT_EQ(image_format_png     ,improc::ImageFormat::Value::kPNG);
    EXPECT_EQ(image_format_jpeg    ,improc::ImageFormat::Value::kJPEG);
    EXPECT_EQ(image_format_jpeg2000,improc::ImageFormat::Value::kJPEG2000);
}

TEST(ImageFormat,TestConstructorFromUpperString) {
    improc::ImageFormat image_format_png      {"PNG"};
    improc::ImageFormat image_format_jpeg     {"JPEG"};
    improc::ImageFormat image_format_jpeg2000 {"JPEG2000"};
    EXPECT_EQ(image_format_png     ,improc::ImageFormat::Value::kPNG);
    EXPECT_EQ(image_format_jpeg    ,improc::ImageFormat::Value::kJPEG);
    EXPECT_EQ(image_format_jpeg2000,improc::ImageFormat::Value::kJPEG2000);
}

TEST(ImageFormat,TestInvalidImageFormatConstructor) {
    EXPECT_THROW(improc::ImageFormat image_format {"invalid"},std::out_of_range);
}

TEST(ImageFormat,TestConstructorFromClass) {
    EXPECT_EQ(improc::ImageFormat::kPNG     ,improc::ImageFormat::Value::kPNG);
    EXPECT_EQ(improc::ImageFormat::kJPEG    ,improc::ImageFormat::Value::kJPEG);
    EXPECT_EQ(improc::ImageFormat::kJPEG2000,improc::ImageFormat::Value::kJPEG2000);
}

TEST(ImageFormat,TestToString) {
    improc::ImageFormat image_format_png      {"png"};
    improc::ImageFormat image_format_jpeg     {"jpeg"};
    improc::ImageFormat image_format_jpeg2000 {"jpeg2000"};
    EXPECT_EQ(image_format_png.ToString()     ,"PNG");
    EXPECT_EQ(image_format_jpeg.ToString()    ,"JPEG");
    EXPECT_EQ(image_format_jpeg2000.ToString(),"JPEG2000");
}

TEST(ImageFormat,TestToOpenCV) {
    improc::ImageFormat image_format_png      {"png"};
    improc::ImageFormat image_format_jpeg     {"jpeg"};
    improc::ImageFormat image_format_jpeg2000 {"jpeg2000"};
    EXPECT_EQ(image_format_png.ToOpenCV()     ,".png");
    EXPECT_EQ(image_format_jpeg.ToOpenCV()    ,".jpg");
    EXPECT_EQ(image_format_jpeg2000.ToOpenCV(),".jp2");
}
