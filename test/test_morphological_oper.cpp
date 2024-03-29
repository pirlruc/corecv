#include <gtest/gtest.h>

#include <improc/corecv/structures/morphological_oper.hpp>

TEST(MorphologicalOper,TestEmptyThresholdTypeConstructor) {
    improc::MorphologicalOper morph_oper {};
    EXPECT_EQ(morph_oper,improc::MorphologicalOper::Value::kDilate);
}

TEST(MorphologicalOper,TestConstructorFromValue) {
    improc::MorphologicalOper morph_oper {improc::MorphologicalOper::Value::kErode};
    EXPECT_EQ(morph_oper,improc::MorphologicalOper::Value::kErode);
}

TEST(MorphologicalOper,TestConstructorFromLowerString) {
    EXPECT_EQ(improc::MorphologicalOper("dilate"),improc::MorphologicalOper::Value::kDilate);
    EXPECT_EQ(improc::MorphologicalOper("erode") ,improc::MorphologicalOper::Value::kErode);
    EXPECT_EQ(improc::MorphologicalOper("open")  ,improc::MorphologicalOper::Value::kOpen);
    EXPECT_EQ(improc::MorphologicalOper("close") ,improc::MorphologicalOper::Value::kClose);
}

TEST(MorphologicalOper,TestConstructorFromUpperString) {
    EXPECT_EQ(improc::MorphologicalOper("DILATE"),improc::MorphologicalOper::Value::kDilate);
    EXPECT_EQ(improc::MorphologicalOper("ERODE") ,improc::MorphologicalOper::Value::kErode);
    EXPECT_EQ(improc::MorphologicalOper("OPEN")  ,improc::MorphologicalOper::Value::kOpen);
    EXPECT_EQ(improc::MorphologicalOper("CLOSE") ,improc::MorphologicalOper::Value::kClose);
}

TEST(MorphologicalOper,TestInvalidMorphOperConstructor) {
    EXPECT_THROW(improc::MorphologicalOper morph_oper {"invalid"},std::out_of_range);
}

TEST(MorphologicalOper,TestConstructorFromClass) {
    EXPECT_EQ(improc::MorphologicalOper::kDilate,improc::MorphologicalOper::Value::kDilate);
    EXPECT_EQ(improc::MorphologicalOper::kErode ,improc::MorphologicalOper::Value::kErode);
    EXPECT_EQ(improc::MorphologicalOper::kOpen  ,improc::MorphologicalOper::Value::kOpen);
    EXPECT_EQ(improc::MorphologicalOper::kClose ,improc::MorphologicalOper::Value::kClose);
}

TEST(MorphologicalOper,TestToString) {
    improc::MorphologicalOper morph_oper_dilate{"dilate"};
    improc::MorphologicalOper morph_oper_erode {"erode"};
    improc::MorphologicalOper morph_oper_open  {"open"};
    improc::MorphologicalOper morph_oper_close {"close"};
    EXPECT_EQ(morph_oper_dilate.ToString(),"Dilate");
    EXPECT_EQ(morph_oper_erode.ToString() ,"Erode");
    EXPECT_EQ(morph_oper_open.ToString()  ,"Open");
    EXPECT_EQ(morph_oper_close.ToString() ,"Close");
}

TEST(MorphologicalOper,TestToOpenCV) {
    improc::MorphologicalOper morph_oper_dilate{"dilate"};
    improc::MorphologicalOper morph_oper_erode {"erode"};
    improc::MorphologicalOper morph_oper_open  {"open"};
    improc::MorphologicalOper morph_oper_close {"close"};
    EXPECT_EQ(morph_oper_dilate.ToOpenCV(),cv::MORPH_DILATE);
    EXPECT_EQ(morph_oper_erode.ToOpenCV() ,cv::MORPH_ERODE);
    EXPECT_EQ(morph_oper_open.ToOpenCV()  ,cv::MORPH_OPEN);
    EXPECT_EQ(morph_oper_close.ToOpenCV() ,cv::MORPH_CLOSE);
}
