#include <improc/corecv/structures/interpolation_type.hpp>

/**
 * @brief Construct a new improc::InterpolationType object
 */
improc::InterpolationType::InterpolationType() : value_(improc::InterpolationType::kLinear) {};

/**
 * @brief Construct a new improc::InterpolationType object
 * 
 * @param interpolation_type_str - interpolation type description as string
 */
improc::InterpolationType::InterpolationType(const std::string& interpolation_type_str)
{
    IMPROC_CORECV_LOGGER_TRACE("Creating interpolation type from string {}...", interpolation_type_str);
    static const std::unordered_map<std::string,InterpolationType::Value> kToElemType = { {"linear" ,InterpolationType::Value::kLinear }
                                                                                        , {"cubic"  ,InterpolationType::Value::kCubic  }
                                                                                        , {"nearest",InterpolationType::Value::kNearest}
                                                                                        };
    this->value_ = kToElemType.at(improc::String::ToLower(std::move(interpolation_type_str)));
}
