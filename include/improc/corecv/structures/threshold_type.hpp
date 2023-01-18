#ifndef IMPROC_CORECV_THRESHOLD_TYPE_HPP
#define IMPROC_CORECV_THRESHOLD_TYPE_HPP

#include <improc/improc_defs.hpp>
#include <improc/corecv/logger_improc.hpp>
#include <improc/infrastructure/string.hpp>

#include <opencv2/imgproc.hpp>

namespace improc 
{
    /**
     * @brief Threshold type methods and utilities
     */
    class ThresholdType final
    {
        public:
            enum Value : IMPROC_ENUM_KEY_TYPE
            {
                    kOtsu   = 0
                ,   kBinary = 1
            };

        private:
            Value                           value_;

        public:
            ThresholdType();                              
            ThresholdType(const std::string& threshold_type_str);

            /**
             * @brief Construct a new improc::ThresholdType object
             * 
             * @param threshold_type_value - threshold type value
             */
            constexpr                       ThresholdType(Value threshold_type_value): value_(std::move(threshold_type_value)) {}

            /**
             * @brief Obtain threshold type value
             */
            constexpr operator              Value()     const {return this->value_;}

            /**
             * @brief Obtain threshold type string description
             */
            constexpr std::string_view      ToString()  const
            {
                switch (this->value_)
                {
                    case ThresholdType::Value::kOtsu  : return "Otsu";    break;
                    case ThresholdType::Value::kBinary: return "Binary";  break;
                }
            }

            /**
             * @brief Obtain threshold type OpenCV code
             */
            constexpr cv::ThresholdTypes    ToOpenCV()  const
            {
                switch (this->value_)
                {
                    case ThresholdType::Value::kOtsu  : return cv::THRESH_OTSU;    break;
                    case ThresholdType::Value::kBinary: return cv::THRESH_BINARY;  break;
                }
            }
    };
}

#endif
