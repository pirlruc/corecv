#include <gtest/gtest.h>

#include <improc/corecv/image.hpp>

TEST(Image,TestEmptyImageConstructor) {
    improc::Image image_empty {};
    EXPECT_TRUE(image_empty.get_data().empty());
}

TEST(Image,TestSetImageToEmptyImage) {
    improc::Image image {};
    image.set_data(cv::Mat::zeros(10,10,CV_8U));
    EXPECT_FALSE(image.get_data().empty());
}

TEST(Image,TestSetInvalidImage) {
    improc::Image image {};
    EXPECT_THROW(image.set_data(cv::Mat::zeros(10,10,CV_16S)),improc::not_supported_data_type);
}

TEST(Image,TestImageConstructor) {
    improc::Image image {cv::Mat::zeros(10,10,CV_8U)};
    EXPECT_FALSE(image.get_data().empty());
}

TEST(Image,TestInvalidImageConstructor) {
    EXPECT_THROW(improc::Image image {cv::Mat::zeros(10,10,CV_16S)},improc::not_supported_data_type);
}

TEST(Image,TestGetImage) {
    cv::Mat image_data = cv::Mat::ones(3,5,CV_8U);
    improc::Image image {image_data};
    EXPECT_EQ(image.get_data().at<uint8_t>(0,0),1);
    image_data.at<uint8_t>(0,0) = 20;
    EXPECT_EQ(image.get_data().at<uint8_t>(0,0),20);
}

TEST(Image,TestCloneImage) {
    cv::Mat image_data = cv::Mat::ones(3,5,CV_8U);
    improc::Image image {image_data};
    improc::Image clone = image.Clone();
    EXPECT_EQ(clone.get_data().at<uint8_t>(0,0),1);
    image_data.at<uint8_t>(0,0) = 20;
    EXPECT_EQ(image.get_data().at<uint8_t>(0,0),20);
    EXPECT_EQ(clone.get_data().at<uint8_t>(0,0),1);
}

TEST(ColorSpaceImage,TestEmptyImageConstructor) {
    improc::ColorSpaceImage image_empty {};
    EXPECT_TRUE(image_empty.get_data().empty());
    EXPECT_EQ(image_empty.get_color_space(),improc::ColorSpace::kRGB);
}

TEST(ColorSpaceImage,TestSetToEmptyImage) {
    improc::ColorSpaceImage image {};
    image.set_data(cv::Mat::zeros(10,10,CV_8UC3));
    image.set_color_space(improc::ColorSpace::kBGR);
    EXPECT_FALSE(image.get_data().empty());
    EXPECT_EQ(image.get_color_space(),improc::ColorSpace::kBGR);
}

TEST(ColorSpaceImage,TestSetInvalidImage) {
    improc::ColorSpaceImage image {};
    EXPECT_THROW(image.set_data(cv::Mat::zeros(10,10,CV_16S)),improc::not_supported_data_type);
}

TEST(ColorSpaceImage,TestSetInvalidColorSpace) {
    improc::ColorSpaceImage image {};
    EXPECT_THROW(image.set_color_space(improc::ColorSpace::kBGR),improc::invalid_color_space);
}

TEST(ColorSpaceImage,TestImageDataConstructor) {
    improc::ColorSpaceImage image {cv::Mat::zeros(10,10,CV_8UC3),improc::ColorSpace::kBGR};
    EXPECT_FALSE(image.get_data().empty());
    EXPECT_EQ(image.get_color_space(),improc::ColorSpace::kBGR);
}

TEST(ColorSpaceImage,TestGet) {
    cv::Mat image_data = cv::Mat::ones(3,5,CV_8UC3);
    improc::ColorSpaceImage image {image_data,improc::ColorSpace::kBGR};
    image_data.at<uint8_t>(0,0) = 20;
    EXPECT_EQ(image.get_data().at<uint8_t>(0,0),20);
    EXPECT_EQ(image.get_color_space(),improc::ColorSpace::kBGR);
}

TEST(ColorSpaceImage,TestCloneImage) {
    cv::Mat image_data = cv::Mat::ones(3,5,CV_8UC3);
    improc::ColorSpaceImage image {image_data,improc::ColorSpace::kBGR};
    improc::ColorSpaceImage clone = image.Clone();
    EXPECT_EQ(clone.get_data().at<uint8_t>(0,0),1);
    image_data.at<uint8_t>(0,0) = 20;
    EXPECT_EQ(image.get_data().at<uint8_t>(0,0),20);
    EXPECT_EQ(image.get_color_space(),improc::ColorSpace::kBGR);
    EXPECT_EQ(clone.get_data().at<uint8_t>(0,0),1);
    EXPECT_EQ(clone.get_color_space(),improc::ColorSpace::kBGR);
}

TEST(ColorSpaceImage,TestConvertToSameColorSpace) {
    cv::Mat image_data = cv::Mat::ones(3,5,CV_8UC3);
    improc::ColorSpaceImage image {image_data,improc::ColorSpace::kBGR};
    EXPECT_EQ(image.get_data().channels(),3);
    image.ConvertToColorSpace(improc::ColorSpace::kBGR);
    EXPECT_EQ(image.get_data().channels(),3);
    EXPECT_EQ(image.get_color_space(),improc::ColorSpace::kBGR);
}

TEST(ColorSpaceImage,TestConvertToDifferentColorSpace) {
    cv::Mat image_data = cv::Mat::ones(3,5,CV_8UC3);
    improc::ColorSpaceImage image {image_data,improc::ColorSpace::kBGR};
    EXPECT_EQ(image.get_data().channels(),3);
    image.ConvertToColorSpace(improc::ColorSpace::kGray);
    EXPECT_EQ(image.get_data().channels(),1);
    EXPECT_EQ(image.get_color_space(),improc::ColorSpace::kGray);
}
