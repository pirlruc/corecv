#include <improc/corecv/structures/threshold_type.hpp>

/**
 * @brief Construct a new improc::ThresholdType object
 */
improc::ThresholdType::ThresholdType() : value_(improc::ThresholdType::kOtsu) {};

/**
 * @brief Construct a new improc::ThresholdType object
 * 
 * @param threshold_type_str - threshold type description as string
 */
improc::ThresholdType::ThresholdType(const std::string& threshold_type_str)
{
    IMPROC_CORECV_LOGGER_TRACE("Creating threshold type from string {}...", threshold_type_str);
    static const std::unordered_map<std::string,ThresholdType::Value> kToElemType = { {"otsu"  ,ThresholdType::Value::kOtsu  }
                                                                                    , {"binary",ThresholdType::Value::kBinary} 
                                                                                    };
    this->value_ = kToElemType.at(improc::String::ToLower(std::move(threshold_type_str)));
}
