#include <improc/corecv/structures/morphological_oper.hpp>

/**
 * @brief Construct a new improc::MorphologicalOper object
 */
improc::MorphologicalOper::MorphologicalOper() : value_(improc::MorphologicalOper::kDilate) {};

/**
 * @brief Construct a new improc::MorphologicalOper object
 * 
 * @param morphological_oper_str - morphological operation description as string
 */
improc::MorphologicalOper::MorphologicalOper(const std::string& morphological_oper_str)
{
    IMPROC_CORECV_LOGGER_TRACE("Creating morphological operation from string {}...", morphological_oper_str);
    static const std::unordered_map<std::string,MorphologicalOper::Value> kToElemType = { {"dilate",MorphologicalOper::Value::kDilate}
                                                                                        , {"erode" ,MorphologicalOper::Value::kErode }
                                                                                        , {"open"  ,MorphologicalOper::Value::kOpen  }
                                                                                        , {"close" ,MorphologicalOper::Value::kClose } 
                                                                                        };
    this->value_ = kToElemType.at(improc::String::ToLower(std::move(morphological_oper_str)));
}
