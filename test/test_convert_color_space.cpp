#include <gtest/gtest.h>

#include <improc/services/convert_color_space.hpp>
#include <improc_corecv_test_config.hpp>

TEST(ConvertColorSpace,TestLoadWithoutToColorSpace) {
    std::string filepath = std::string(IMPROC_CORECV_TEST_FOLDER) + "/test/data/test_color_conversion_without_to.json";
    improc::JsonFile json_file {filepath};
    Json::Value json_content = json_file.Read();

    improc::StringKeyHeterogeneousConvertColorSpace convert {};
    EXPECT_THROW(convert.Load(json_content),improc::file_processing_error);
}

TEST(ConvertColorSpace,TestLoadWithFromColorSpaceArray) {
    std::string filepath = std::string(IMPROC_CORECV_TEST_FOLDER) + "/test/data/test_color_conversion_with_from_array.json";
    improc::JsonFile json_file {filepath};
    Json::Value json_content = json_file.Read();

    improc::StringKeyHeterogeneousConvertColorSpace convert {};
    EXPECT_THROW(convert.Load(json_content),Json::LogicError);
}

TEST(ConvertColorSpace,TestWithoutFromColorSpace) {
    std::string filepath = std::string(IMPROC_CORECV_TEST_FOLDER) + "/test/data/test_color_conversion_without_from.json";
    improc::JsonFile json_file {filepath};
    Json::Value json_content = json_file.Read();

    improc::StringKeyHeterogeneousConvertColorSpace convert {};
    convert.Load(json_content);

    cv::Mat             image_data       = cv::Mat::ones(10,5,CV_8UC3);
    improc::ColorSpace  from_color_space = improc::ColorSpace::kRGB;
    improc::StringKeyHeterogeneousContext cntxt {};
    cntxt.Add("image",image_data);
    cntxt.Add("from_color_space",from_color_space);

    convert.Run(cntxt);    

    improc::ColorSpaceImage image = std::any_cast<improc::ColorSpaceImage>(cntxt["image"]);
    EXPECT_EQ(image.get_color_space(),improc::ColorSpace::kGray);
    EXPECT_EQ(image.get_data().channels(),1);    
}

TEST(ConvertColorSpace,TestWithoutFromColorSpaceInContext) {
    std::string filepath = std::string(IMPROC_CORECV_TEST_FOLDER) + "/test/data/test_color_conversion_without_from.json";
    improc::JsonFile json_file {filepath};
    Json::Value json_content = json_file.Read();

    improc::StringKeyHeterogeneousConvertColorSpace convert {};
    convert.Load(json_content);

    cv::Mat             image_data       = cv::Mat::ones(10,5,CV_8UC3);
    improc::StringKeyHeterogeneousContext cntxt {};
    cntxt.Add("image",image_data);

    EXPECT_THROW(convert.Run(cntxt),improc::not_found_key);
}

TEST(ConvertColorSpace,TestWithFromColorSpaceSingleConversion) {
    std::string filepath = std::string(IMPROC_CORECV_TEST_FOLDER) + "/test/data/test_single_color_conversion_with_from.json";
    improc::JsonFile json_file {filepath};
    Json::Value json_content = json_file.Read();

    improc::StringKeyHeterogeneousConvertColorSpace convert {};
    convert.Load(json_content);

    cv::Mat             image_data       = cv::Mat::ones(10,5,CV_8UC3);
    improc::StringKeyHeterogeneousContext cntxt {};
    cntxt.Add("image",image_data);

    convert.Run(cntxt);    

    improc::ColorSpaceImage image = std::any_cast<improc::ColorSpaceImage>(cntxt.Get("image"));
    EXPECT_EQ(image.get_color_space(),improc::ColorSpace::kBGR);
    EXPECT_EQ(image.get_data().channels(),3);    
}

TEST(ConvertColorSpace,TestWithFromColorSpaceSequenceConversion) {
    std::string filepath = std::string(IMPROC_CORECV_TEST_FOLDER) + "/test/data/test_sequence_color_conversion_with_from.json";
    improc::JsonFile json_file {filepath};
    Json::Value json_content = json_file.Read();

    improc::StringKeyHeterogeneousConvertColorSpace convert {};
    convert.Load(json_content);

    cv::Mat             image_data       = cv::Mat::ones(10,5,CV_8UC3);
    improc::StringKeyHeterogeneousContext cntxt {};
    cntxt.Add("image",image_data);

    convert.Run(cntxt);    

    improc::ColorSpaceImage image = std::any_cast<improc::ColorSpaceImage>(cntxt.Get("image"));
    EXPECT_EQ(image.get_color_space(),improc::ColorSpace::kGray);
    EXPECT_EQ(image.get_data().channels(),1);    
}
