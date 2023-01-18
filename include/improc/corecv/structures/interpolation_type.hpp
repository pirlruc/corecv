#ifndef IMPROC_CORECV_INTERPOLATION_TYPE_HPP
#define IMPROC_CORECV_INTERPOLATION_TYPE_HPP

#include <improc/improc_defs.hpp>
#include <improc/corecv/logger_improc.hpp>
#include <improc/infrastructure/string.hpp>

#include <opencv2/imgproc.hpp>

namespace improc 
{
    /**
     * @brief Interpolation type methods and utilities
     */
    class InterpolationType final
    {
        public:
            enum Value : IMPROC_ENUM_KEY_TYPE
            {
                    kLinear  = 0
                ,   kCubic   = 1
                ,   kNearest = 2
            };

        private:
            Value                               value_;

        public:
            InterpolationType();                              
            InterpolationType(const std::string& interpolation_type_str);

            /**
             * @brief Construct a new improc::InterpolationType object
             * 
             * @param interpolation_type_value - interpolation type value
             */
            constexpr                           InterpolationType(Value interpolation_type_value): value_(std::move(interpolation_type_value)) {}

            /**
             * @brief Obtain interpolation type value
             */
            constexpr operator                  Value()     const {return this->value_;}

            /**
             * @brief Obtain interpolation type string description
             */
            constexpr std::string_view          ToString()  const
            {
                switch (this->value_)
                {
                    case InterpolationType::Value::kLinear : return "Linear";   break;
                    case InterpolationType::Value::kCubic  : return "Cubic";    break;
                    case InterpolationType::Value::kNearest: return "Nearest";  break;
                }
            }

            /**
             * @brief Obtain interpolation type OpenCV code
             */
            constexpr cv::InterpolationFlags    ToOpenCV()  const
            {
                switch (this->value_)
                {
                    case InterpolationType::Value::kLinear : return cv::INTER_LINEAR;   break;
                    case InterpolationType::Value::kCubic  : return cv::INTER_CUBIC;    break;
                    case InterpolationType::Value::kNearest: return cv::INTER_NEAREST;  break;
                }
            }
    };
}

#endif