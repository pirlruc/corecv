#include <improc/corecv/structures/kernel_shape.hpp>

/**
 * @brief Construct a new improc::KernelShape object
 */
improc::KernelShape::KernelShape() : value_(improc::KernelShape::kRectangle) {};

/**
 * @brief Construct a new improc::KernelShape object
 * 
 * @param kernel_shape_str - kernel shape description as string
 */
improc::KernelShape::KernelShape(const std::string& kernel_shape_str)
{
    IMPROC_CORECV_LOGGER_TRACE("Creating kernel shape from string {}...", kernel_shape_str);
    static const std::unordered_map<std::string,KernelShape::Value> kToElemType = { {"rectangle",KernelShape::Value::kRectangle}
                                                                                  , {"ellipse"  ,KernelShape::Value::kEllipse  } 
                                                                                  };
    this->value_ = kToElemType.at(improc::String::ToLower(std::move(kernel_shape_str)));
}
