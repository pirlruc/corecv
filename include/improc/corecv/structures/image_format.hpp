#ifndef IMPROC_CORECV_IMAGE_FORMAT_HPP
#define IMPROC_CORECV_IMAGE_FORMAT_HPP

#include <improc/improc_defs.hpp>
#include <improc/corecv/logger_improc.hpp>
#include <improc/infrastructure/string.hpp>

#include <opencv2/core.hpp>

namespace improc 
{
    /**
     * @brief Image format methods and utilities
     */
    class IMPROC_API ImageFormat final
    {
        public:
            enum Value : IMPROC_ENUM_KEY_TYPE
            {
                    kPNG      = 0
                ,   kJPEG     = 1
                ,   kJPEG2000 = 2
            };

        private:
            Value                       value_;

        public:
            ImageFormat();                              
            explicit ImageFormat(const std::string& image_format_str);

            /**
             * @brief Construct a new improc::ImageFormat object
             * 
             * @param image_format_value - image format value
             */
            constexpr explicit          ImageFormat(Value image_format_value): value_(std::move(image_format_value)) {}

            /**
             * @brief Obtain image format value
             */
            constexpr operator          Value()     const {return this->value_;}

            /**
             * @brief Obtain image format string description
             */
            constexpr std::string_view  ToString()  const
            {
                switch (this->value_)
                {
                    case ImageFormat::Value::kPNG     : return "PNG";       break;
                    case ImageFormat::Value::kJPEG    : return "JPEG";      break;
                    case ImageFormat::Value::kJPEG2000: return "JPEG2000";  break;
                    default:
                        throw improc::key_error("ToString method not defined for image format enum");
                }
            }

            /**
             * @brief Obtain image format OpenCV code
             */
            constexpr std::string_view  ToOpenCV()  const
            {
                switch (this->value_)
                {
                    case ImageFormat::Value::kPNG     : return ".png";  break;
                    case ImageFormat::Value::kJPEG    : return ".jpg";  break;
                    case ImageFormat::Value::kJPEG2000: return ".jp2";  break;
                    default:
                        throw improc::key_error("ToOpenCV method not defined for image format enum");
                }
            }
    };
}

#endif
