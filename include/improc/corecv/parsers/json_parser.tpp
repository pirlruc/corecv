/**
 * @brief Construct a new improc::Point object
 * 
 * @tparam DataType - data type for point parsing utility
 */
template <typename DataType>
improc::Point<DataType>::Point(): x(0),y(0) 
{
    static_assert(std::is_same_v<DataType,int> || std::is_same_v<DataType,double>, "Point parsing not defined for data type");
};

/**
 * @brief Construct a new improc::Point object
 * 
 * @tparam DataType - data type for point parsing utility
 * @param json_point - configuration json for point
 */
template <typename DataType>
improc::Point<DataType>::Point(const Json::Value& json_point): improc::Point<DataType>()
{
    IMPROC_CORECV_LOGGER_TRACE("Parsing point json...");
    static const std::string kXPositionKey = "x";
    static const std::string kYPositionKey = "y";
    if (json_point.isMember(kXPositionKey) == false)
    {
        std::string error_message = fmt::format("Key {}-position is missing from json",kXPositionKey);
        IMPROC_CORECV_LOGGER_ERROR("ERROR_01: " + error_message);
        throw improc::json_error(std::move(error_message));
    }
    if (json_point.isMember(kYPositionKey) == false)
    {
        std::string error_message = fmt::format("Key {}-position is missing from json",kYPositionKey);
        IMPROC_CORECV_LOGGER_ERROR("ERROR_02: " + error_message);
        throw improc::json_error(std::move(error_message));
    }
    this->x = improc::json::ReadElement<DataType>(json_point[kXPositionKey]);
    this->y = improc::json::ReadElement<DataType>(json_point[kYPositionKey]);
}

/**
 * @brief Construct a new improc::Size object
 * 
 * @tparam DataType - data type for size parsing utility
 */
template <typename DataType>
improc::Size<DataType>::Size(): width(0),height(0) 
{
    static_assert(std::is_same_v<DataType,int> || std::is_same_v<DataType,double>, "Size parsing not defined for data type");
};

/**
 * @brief Construct a new improc::Size object
 * 
 * @tparam DataType - data type for size parsing utility
 * @param json_size - configuration json for size
 */
template <typename DataType>
improc::Size<DataType>::Size(const Json::Value& json_size): improc::Size<DataType>()
{
    IMPROC_CORECV_LOGGER_TRACE("Parsing size json...");
    static const std::string kWidthKey  = "width";
    static const std::string kHeightKey = "height";
    if (json_size.isMember(kWidthKey) == false)
    {
        std::string error_message = fmt::format("Key {} is missing from json",kWidthKey);
        IMPROC_CORECV_LOGGER_ERROR("ERROR_01: " + error_message);
        throw improc::json_error(std::move(error_message));
    }
    if (json_size.isMember(kHeightKey) == false)
    {
        std::string error_message = fmt::format("Key {} is missing from json",kHeightKey);
        IMPROC_CORECV_LOGGER_ERROR("ERROR_02: " + error_message);
        throw improc::json_error(std::move(error_message));
    }
    this->width  = improc::json::ReadElement<DataType>(json_size[kWidthKey]);
    this->height = improc::json::ReadElement<DataType>(json_size[kHeightKey]);
}

template<>
inline cv::Point improc::json::ReadElement(const Json::Value& json_elem)
{
    IMPROC_CORECV_LOGGER_TRACE("Reading cv::Point json element...");
    improc::Point<int> point {std::move(json_elem)};
    return cv::Point(point.x, point.y);
}

template<>
inline cv::Point2d improc::json::ReadElement(const Json::Value& json_elem)
{
    IMPROC_CORECV_LOGGER_TRACE("Reading cv::Point json element...");
    improc::Point<double> point {std::move(json_elem)};
    return cv::Point2d(point.x, point.y);
}

template<>
inline cv::Size improc::json::ReadElement(const Json::Value& json_elem)
{
    IMPROC_CORECV_LOGGER_TRACE("Reading cv::Size json element...");
    improc::Size<int> size {std::move(json_elem)};
    return cv::Size(size.width, size.height);
}

template<>
inline cv::Size2d improc::json::ReadElement(const Json::Value& json_elem)
{
    IMPROC_CORECV_LOGGER_TRACE("Reading cv::Size json element...");
    improc::Size<double> size {std::move(json_elem)};
    return cv::Size2d(size.width, size.height);
}

template<typename KeyType>
inline KeyType improc::json::ReadPositiveSize(const Json::Value& json_size)
{
    static_assert(std::is_same_v<KeyType,cv::Size> || std::is_same_v<KeyType,cv::Size2d>, "Parsing not defined for data type");
    IMPROC_CORECV_LOGGER_TRACE("Reading positive {} json element...",typeid(KeyType).name());
    KeyType size = improc::json::ReadElement<KeyType>(std::move(json_size));
    if (size.width <= 0.0)
    {
        std::string error_message = fmt::format("Width should be greater than zero. Width gave was {}",size.width);
        IMPROC_CORECV_LOGGER_ERROR("ERROR_01: " + error_message);
        throw improc::value_error(std::move(error_message));
    }
    if (size.height <= 0.0)
    {
        std::string error_message = fmt::format("Height should be greater than zero. Height gave was {}",size.height);
        IMPROC_CORECV_LOGGER_ERROR("ERROR_02: " + error_message);
        throw improc::value_error(std::move(error_message));
    }
    return size;
}
