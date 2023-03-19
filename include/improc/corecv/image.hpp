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
    class IMPROC_API Image
    {
        protected:
            cv::Mat                     data_;

        public:
            Image();
            explicit Image(const cv::Mat& image_data);

            void                        set_data(const cv::Mat& image_data);
            cv::Mat                     get_data()  const;

            Image                       Clone()     const;

            // void                        Resize(const cv::Size&   to_image_size, const InterpolationType& interpolation);
            // void                        Resize(const cv::Size2d& scaling,       const InterpolationType& interpolation);
    };


    // TODO: Review implementation and add tests
    class IMPROC_API ColorSpaceImage : public Image
    {
        private:
            ColorSpace                  color_space_;

        public:
            ColorSpaceImage();

            template <typename ColorSpaceType = improc::ColorSpace::Value>
            ColorSpaceImage(const cv::Mat& image_data, const ColorSpaceType& color_space) : Image(std::move(image_data))
            {
                IMPROC_CORECV_LOGGER_TRACE("Creating color space image object...");    
                this->set_color_space(color_space);
            }

            template <typename ColorSpaceType = improc::ColorSpace::Value>
            void                        set_color_space(const ColorSpaceType& color_space)
            {
                IMPROC_CORECV_LOGGER_TRACE("Setting color space...");
                improc::ColorSpace color_space_object {};
                if constexpr (std::is_same_v<ColorSpaceType,improc::ColorSpace>)
                {
                    color_space_object = std::move(color_space);
                }
                else if constexpr (std::is_same_v<ColorSpaceType,improc::ColorSpace::Value>)
                {
                    color_space_object = improc::ColorSpace(std::move(color_space));
                }
                else
                {
                    static_assert(improc::dependent_false_v<ColorSpaceType>,"set_color_space not defined for color space type");
                }

                if (this->data_.channels() != color_space_object.GetNumberChannels())
                {
                    IMPROC_CORECV_LOGGER_ERROR  ( "ERROR_01: Invalid color space for image. Expected {} channels but image has {}."
                                                , color_space_object.GetNumberChannels(), this->data_.channels() );
                    throw improc::invalid_color_space();
                }
                this->color_space_ = color_space_object;
            }

            ColorSpace                  get_color_space()   const;

            ColorSpaceImage             Clone()             const;

            template <typename ColorSpaceType = improc::ColorSpace::Value>
            void                        ConvertToColorSpace(const ColorSpaceType& to_color_space)
            {
                IMPROC_CORECV_LOGGER_TRACE  ("Converting color space image from {} to {}..."
                                            , this->color_space_.ToString(), to_color_space.ToString() );
                if (this->color_space_ == to_color_space)
                {
                    IMPROC_CORECV_LOGGER_DEBUG("Color conversion not performed. Image is already in target color space.");
                }
                else
                {
                    cv::cvtColor(this->data_,this->data_,this->color_space_.GetColorConversionCode(to_color_space));
                    this->set_color_space(to_color_space);
                }
            }
    };
}

#endif