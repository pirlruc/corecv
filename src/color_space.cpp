#include <improc/corecv/structures/color_space.hpp>

/**
 * @brief Construct a new improc::ColorSpace object
 */
improc::ColorSpace::ColorSpace() : value_(improc::ColorSpace::kRGB) {};

/**
 * @brief Construct a new improc::ColorSpace object
 * 
 * @param color_space_str - color space description as string
 */
improc::ColorSpace::ColorSpace(const std::string& color_space_str)
{
    IMPROC_CORECV_LOGGER_TRACE("Creating color space from string {}...", color_space_str);
    static const std::unordered_map<std::string,ColorSpace::Value> kToElemType = { {"rgb" ,ColorSpace::Value::kRGB }
                                                                                 , {"bgr" ,ColorSpace::Value::kBGR }
                                                                                 , {"rgba",ColorSpace::Value::kRGBA}
                                                                                 , {"bgra",ColorSpace::Value::kBGRA}
                                                                                 , {"gray",ColorSpace::Value::kGray}
                                                                                 };
    this->value_ = kToElemType.at(improc::String::ToLower(std::move(color_space_str)));
}
