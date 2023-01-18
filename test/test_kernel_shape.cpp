#include <gtest/gtest.h>

#include <improc/corecv/structures/kernel_shape.hpp>

TEST(KernelShape,TestEmptyKernelShapeConstructor) {
    improc::KernelShape kernel {};
    EXPECT_EQ(kernel,improc::KernelShape::Value::kRectangle);
}

TEST(KernelShape,TestConstructorFromValue) {
    improc::KernelShape kernel {improc::KernelShape::Value::kEllipse};
    EXPECT_EQ(kernel,improc::KernelShape::Value::kEllipse);
}

TEST(KernelShape,TestConstructorFromLowerString) {
    improc::KernelShape kernel_rectangle {"rectangle"};
    improc::KernelShape kernel_ellipse   {"ellipse"};
    EXPECT_EQ(kernel_rectangle,improc::KernelShape::Value::kRectangle);
    EXPECT_EQ(kernel_ellipse  ,improc::KernelShape::Value::kEllipse);
}

TEST(KernelShape,TestConstructorFromUpperString) {
    improc::KernelShape kernel_rectangle {"RECTANGLE"};
    improc::KernelShape kernel_ellipse   {"ELLIPSE"};
    EXPECT_EQ(kernel_rectangle,improc::KernelShape::Value::kRectangle);
    EXPECT_EQ(kernel_ellipse  ,improc::KernelShape::Value::kEllipse);
}

TEST(KernelShape,TestInvalidThresholdConstructor) {
    EXPECT_THROW(improc::KernelShape kernel {"invalid"},std::out_of_range);
}

TEST(KernelShape,TestConstructorFromClass) {
    EXPECT_EQ(improc::KernelShape::kRectangle,improc::KernelShape::Value::kRectangle);
    EXPECT_EQ(improc::KernelShape::kEllipse  ,improc::KernelShape::Value::kEllipse);
}

TEST(KernelShape,TestToString) {
    improc::KernelShape kernel_rectangle {"rectangle"};
    improc::KernelShape kernel_ellipse   {"ellipse"};
    EXPECT_EQ(kernel_rectangle.ToString(),"Rectangle");
    EXPECT_EQ(kernel_ellipse.ToString()  ,"Ellipse");
}

TEST(KernelShape,TestToOpenCV) {
    improc::KernelShape kernel_rectangle {"rectangle"};
    improc::KernelShape kernel_ellipse   {"ellipse"};
    EXPECT_EQ(kernel_rectangle.ToOpenCV(),cv::MORPH_RECT);
    EXPECT_EQ(kernel_ellipse.ToOpenCV()  ,cv::MORPH_ELLIPSE);
}
