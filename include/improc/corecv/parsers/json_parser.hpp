#ifndef IMPROC_CORECV_JSON_PARSER_HPP
#define IMPROC_CORECV_JSON_PARSER_HPP

#include <improc/corecv/logger_improc.hpp>
#include <improc/improc_defs.hpp>
#include <improc/infrastructure/parsers/json_parser.hpp>

#include <opencv2/core.hpp>
#include <json/json.h>

namespace improc
{
    /**
     * @brief Point parsing utility. 
     * 
     * @tparam DataType - data type for point parsing utility
     */
    template<typename DataType>
    struct Point final
    {
        static_assert(std::is_same_v<DataType,int> || std::is_same_v<DataType,double>, "Point parsing not defined for data type");

        DataType x;
        DataType y;

        Point();
        explicit Point(const Json::Value& json_point);
    };

    /**
     * @brief Size parsing utility. 
     * 
     * @tparam DataType - data type for size parsing utility
     */
    template<typename DataType>
    struct Size final
    {
        static_assert(std::is_same_v<DataType,int> || std::is_same_v<DataType,double>, "Size parsing not defined for data type");

        DataType width;
        DataType height;

        Size();
        explicit Size(const Json::Value& json_size);
    };


    namespace json
    {
        template<typename KeyType>
        IMPROC_API KeyType                  ReadPositiveSize (const Json::Value& json_size);
    }
}

#include <improc/corecv/parsers/json_parser.tpp>

#endif
