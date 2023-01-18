#ifndef IMPROC_CORECV_IMAGE_HPP
#define IMPROC_CORECV_IMAGE_HPP

#include <improc/improc_defs.hpp>
#include <improc/exception.hpp>
#include <improc/corecv/logger_improc.hpp>
#include <improc/corecv/structures/color_space.hpp>
#include <improc/corecv/structures/interpolation_type.hpp>

#include <opencv2/core.hpp>

namespace improc {
    // TODO: Review implementation and add tests
    // TODO: Make compatible with cv::UMat and cv::MatExpr
    class Image
    {
        protected:
            cv::Mat                     data_;

        public:
            Image();
            Image(const cv::Mat& image_data);

            void                        set_data(const cv::Mat& image_data);
            cv::Mat                     get_data()  const;

            Image                       Clone()     const;

            // void                        Resize(const cv::Size&   to_image_size, const InterpolationType& interpolation);
            // void                        Resize(const cv::Size2d& scaling,       const InterpolationType& interpolation);
    };


    // TODO: Review implementation and add tests
    class ColorSpaceImage : public Image
    {
        private:
            ColorSpace                  color_space_;

        public:
            ColorSpaceImage();
            ColorSpaceImage(const cv::Mat& image_data, const ColorSpace& color_space);

            void                        set_color_space(const ColorSpace& color_space);
            ColorSpace                  get_color_space()   const;

            ColorSpaceImage             Clone()             const;

            void                        ConvertToColorSpace(const ColorSpace& to_color_space);
    };
}

#endif