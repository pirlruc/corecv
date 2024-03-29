#ifndef IMPROC_CORECV_COLOR_SPACE_HPP
#define IMPROC_CORECV_COLOR_SPACE_HPP

#include <improc/improc_defs.hpp>
#include <improc/exception.hpp>
#include <improc/corecv/logger_improc.hpp>
#include <improc/infrastructure/string.hpp>

#include <opencv2/imgproc.hpp>

namespace improc 
{
    /**
     * @brief Color space methods and utilities
     */
    class IMPROC_API ColorSpace final
    {
        public:
            enum Value : IMPROC_ENUM_KEY_TYPE
            {
                    kRGBA = 0
                ,   kBGRA = 1
                ,   kRGB  = 2
                ,   kBGR  = 3
                ,   kGray = 4
            };

        private:
            Value                       value_;

        public:
            ColorSpace();                              
            explicit ColorSpace(const std::string& color_space_str);

            /**
             * @brief Construct a new improc::ColorSpace object
             * 
             * @param color_space_value - color space value
             */
            constexpr explicit          ColorSpace(Value color_space_value): value_(std::move(color_space_value)) {}

            /**
             * @brief Obtain color space value
             */
            constexpr operator          Value()     const {return this->value_;}

            /**
             * @brief Obtain color space string description
             */
            constexpr std::string_view  ToString()  const
            {
                switch (this->value_)
                {
                    case ColorSpace::Value::kBGR : return "BGR";  break;
                    case ColorSpace::Value::kRGB : return "RGB";  break;
                    case ColorSpace::Value::kBGRA: return "BGRA"; break;
                    case ColorSpace::Value::kRGBA: return "RGBA"; break;
                    case ColorSpace::Value::kGray: return "Gray"; break;
                    default:
                        throw improc::key_error("ToString method not defined for color space enum");
                }
            }

            /**
             * @brief Obtain color space number of channels
             */
            constexpr unsigned int      GetNumberChannels() const
            {
                switch (this->value_)
                {
                    case ColorSpace::Value::kBGR : return 3;    break;
                    case ColorSpace::Value::kRGB : return 3;    break;
                    case ColorSpace::Value::kBGRA: return 4;    break;
                    case ColorSpace::Value::kRGBA: return 4;    break;
                    case ColorSpace::Value::kGray: return 1;    break;
                    default:
                        throw improc::key_error("GetNumberChannels method not defined for color space enum");                
                }
            }

            /**
             * @brief Obtain OpenCV color conversion code from source to target color space.
             * 
             * @tparam ColorSpaceType - color space data type: improc::ColorSpace or improc::ColorSpace::Value
             * @param to_color_space - target color space
             */
            template<typename ColorSpaceType = improc::ColorSpace::Value>
            constexpr cv::ColorConversionCodes GetColorConversionCode(const ColorSpaceType& to_color_space) const
            {
                improc::ColorSpace::Value to_color_space_value {};
                if constexpr (std::is_same_v<ColorSpaceType,improc::ColorSpace::Value>)
                {
                    to_color_space_value = std::move(to_color_space);
                }
                else if constexpr (std::is_same_v<ColorSpaceType,improc::ColorSpace>)
                {
                    to_color_space_value = std::move(to_color_space).operator improc::ColorSpace::Value();
                }
                else
                {
                    static_assert(improc::dependent_false_v<ColorSpaceType>,"GetColorConversionCode not defined for color space type");
                }

                switch (this->value_)
                {
                    case ColorSpace::Value::kBGR : 
                        switch (std::move(to_color_space_value))
                        {
                            case ColorSpace::Value::kBGR : 
                                throw improc::value_error(fmt::format("Source and target color space {} are the same",this->ToString()));
                                break;
                            case ColorSpace::Value::kRGB : return cv::COLOR_BGR2RGB;                        break;
                            case ColorSpace::Value::kBGRA: return cv::COLOR_BGR2BGRA;                       break;
                            case ColorSpace::Value::kRGBA: return cv::COLOR_BGR2RGBA;                       break;
                            case ColorSpace::Value::kGray: return cv::COLOR_BGR2GRAY;                       break;
                            default:
                                throw improc::key_error("GetColorConversionCode method not defined for color space enum from BGR");
                        }
                        break;

                    case ColorSpace::Value::kRGB :
                        switch (std::move(to_color_space_value))
                        {
                            case ColorSpace::Value::kBGR : return cv::COLOR_RGB2BGR;                        break;
                            case ColorSpace::Value::kRGB : 
                                throw improc::value_error(fmt::format("Source and target color space {} are the same",this->ToString()));
                                break;
                            case ColorSpace::Value::kBGRA: return cv::COLOR_RGB2BGRA;                       break;
                            case ColorSpace::Value::kRGBA: return cv::COLOR_RGB2RGBA;                       break;
                            case ColorSpace::Value::kGray: return cv::COLOR_RGB2GRAY;                       break;
                            default:
                                throw improc::key_error("GetColorConversionCode method not defined for color space enum from RGB");
                        }
                        break;

                    case ColorSpace::Value::kBGRA:
                        switch (std::move(to_color_space_value))
                        {
                            case ColorSpace::Value::kBGR : return cv::COLOR_BGRA2BGR;                       break;
                            case ColorSpace::Value::kRGB : return cv::COLOR_BGRA2RGB;                       break;
                            case ColorSpace::Value::kBGRA: 
                                throw improc::value_error(fmt::format("Source and target color space {} are the same",this->ToString()));
                                break;
                            case ColorSpace::Value::kRGBA: return cv::COLOR_BGRA2RGBA;                      break;
                            case ColorSpace::Value::kGray: return cv::COLOR_BGRA2GRAY;                      break;
                            default:
                                throw improc::key_error("GetColorConversionCode method not defined for color space enum from BGRA");
                        }
                        break;

                    case ColorSpace::Value::kRGBA:
                        switch (std::move(to_color_space_value))
                        {
                            case ColorSpace::Value::kBGR : return cv::COLOR_RGBA2BGR;                       break;
                            case ColorSpace::Value::kRGB : return cv::COLOR_RGBA2RGB;                       break;
                            case ColorSpace::Value::kBGRA: return cv::COLOR_RGBA2BGRA;                      break;
                            case ColorSpace::Value::kRGBA: 
                                throw improc::value_error(fmt::format("Source and target color space {} are the same",this->ToString()));
                                break;
                            case ColorSpace::Value::kGray: return cv::COLOR_RGBA2GRAY;                      break;
                            default:
                                throw improc::key_error("GetColorConversionCode method not defined for color space enum from RGBA");
                        }
                        break;

                    case ColorSpace::Value::kGray:
                        switch (std::move(to_color_space_value))
                        {
                            case ColorSpace::Value::kBGR : return cv::COLOR_GRAY2BGR;                       break;
                            case ColorSpace::Value::kRGB : return cv::COLOR_GRAY2RGB;                       break;
                            case ColorSpace::Value::kBGRA: return cv::COLOR_GRAY2BGRA;                      break;
                            case ColorSpace::Value::kRGBA: return cv::COLOR_GRAY2RGBA;                      break;
                            case ColorSpace::Value::kGray: 
                                throw improc::value_error(fmt::format("Source and target color space {} are the same",this->ToString()));
                                break;
                            default:
                                throw improc::key_error("GetColorConversionCode method not defined for color space enum from Gray");
                        }
                        break;

                    default:
                        throw improc::key_error("GetColorConversionCode method not defined for color space enum");
                }
            }
    };
}

#endif