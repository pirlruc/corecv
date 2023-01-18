#ifndef IMPROC_CORECV_MORPHOLOGICAL_OPER_HPP
#define IMPROC_CORECV_MORPHOLOGICAL_OPER_HPP

#include <improc/improc_defs.hpp>
#include <improc/corecv/logger_improc.hpp>
#include <improc/infrastructure/string.hpp>

#include <opencv2/imgproc.hpp>

namespace improc 
{
    /**
     * @brief Morphological operation methods and utilities
     */
    class MorphologicalOper final
    {
        public:
            enum Value : IMPROC_ENUM_KEY_TYPE
            {
                    kDilate = 0
                ,   kErode  = 1
                ,   kOpen   = 2
                ,   kClose  = 3
            };

        private:
            Value                       value_;

        public:
            MorphologicalOper();                              
            MorphologicalOper(const std::string& morphological_oper_str);

            /**
             * @brief Construct a new improc::MorphologicalOper object
             * 
             * @param morphological_oper_value - morphological operation value
             */
            constexpr                   MorphologicalOper(Value morphological_oper_value): value_(std::move(morphological_oper_value)) {}

            /**
             * @brief Obtain morphological operation value
             */
            constexpr operator          Value()     const {return this->value_;}

            /**
             * @brief Obtain morphological operation string description
             */
            constexpr std::string_view  ToString()  const
            {
                switch (this->value_)
                {
                    case MorphologicalOper::Value::kDilate: return "Dilate";    break;
                    case MorphologicalOper::Value::kErode : return "Erode";     break;
                    case MorphologicalOper::Value::kOpen  : return "Open";      break;
                    case MorphologicalOper::Value::kClose : return "Close";     break;
                }
            }

            /**
             * @brief Obtain morphological operation OpenCV code
             */
            constexpr cv::MorphTypes    ToOpenCV()  const
            {
                switch (this->value_)
                {
                    case MorphologicalOper::Value::kDilate: return cv::MORPH_DILATE;    break;
                    case MorphologicalOper::Value::kErode : return cv::MORPH_ERODE;     break;
                    case MorphologicalOper::Value::kOpen  : return cv::MORPH_OPEN;      break;
                    case MorphologicalOper::Value::kClose : return cv::MORPH_CLOSE;     break;
                }
            }
    };
}

#endif
