#ifndef IMPROC_CORECV_ROTATION_TYPE_HPP
#define IMPROC_CORECV_ROTATION_TYPE_HPP

#include <improc/improc_defs.hpp>
#include <improc/corecv/logger_improc.hpp>
#include <improc/infrastructure/string.hpp>

#include <opencv2/core.hpp>

namespace improc 
{
    /**
     * @brief Rotation type methods and utilities
     */
    class IMPROC_API RotationType final
    {
        public:
            enum Value : IMPROC_ENUM_KEY_TYPE
            {
                    k0Deg   = 0
                ,   k90Deg  = 1
                ,   k180Deg = 2
                ,   k270Deg = 3
            };

        private:
            Value                       value_;

        public:
            RotationType();                              
            explicit RotationType(const std::string& rotation_type_str);

            /**
             * @brief Construct a new improc::RotationType object
             * 
             * @param rotation_type_value - rotation type value
             */
            constexpr explicit          RotationType(Value rotation_type_value): value_(std::move(rotation_type_value)) {}

            /**
             * @brief Obtain rotation type value
             */
            constexpr operator          Value()     const {return this->value_;}

            /**
             * @brief Obtain rotation type string description
             */
            constexpr std::string_view  ToString()  const
            {
                switch (this->value_)
                {
                    case RotationType::Value::k0Deg  : return "0 Degrees";    break;
                    case RotationType::Value::k90Deg : return "90 Degrees";   break;
                    case RotationType::Value::k180Deg: return "180 Degrees";  break;
                    case RotationType::Value::k270Deg: return "270 Degrees";  break;
                }
            }

            //TODO: Start using image class
            cv::Mat                     Apply       (const cv::Mat& image)          const;
            cv::Mat                     ApplyInverse(const cv::Mat& rotated_image)  const;
    };
}

#endif