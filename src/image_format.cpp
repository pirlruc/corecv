#include <improc/corecv/structures/image_format.hpp>

/**
 * @brief Construct a new improc::ImageFormat object
 */
improc::ImageFormat::ImageFormat() : value_(improc::ImageFormat::kPNG) {};

/**
 * @brief Construct a new improc::ImageFormat object
 * 
 * @param image_format_str - image format description as string
 */
improc::ImageFormat::ImageFormat(const std::string& image_format_str)
{
    IMPROC_CORECV_LOGGER_TRACE("Creating image format from string {}...", image_format_str);
    static const std::unordered_map<std::string,ImageFormat::Value> kToElemType = { {"png"     ,ImageFormat::Value::kPNG     }
                                                                                  , {"jpeg"    ,ImageFormat::Value::kJPEG    }
                                                                                  , {"jpeg2000",ImageFormat::Value::kJPEG2000}
                                                                                  };
    this->value_ = kToElemType.at(improc::String::ToLower(std::move(image_format_str)));
}
