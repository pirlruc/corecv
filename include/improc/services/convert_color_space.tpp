template <typename KeyType,typename ContextType>
improc::ConvertColorSpace<KeyType,ContextType>::ConvertColorSpace() : improc::BaseService<KeyType,ContextType>()
                                                                    , from_color_space_(std::optional<improc::ColorSpace>())
                                                                    , to_color_space_(std::vector<improc::ColorSpace>())
{}

template <typename KeyType,typename ContextType>
improc::ConvertColorSpace<KeyType,ContextType>& improc::ConvertColorSpace<KeyType,ContextType>::Load(const Json::Value& service_json)
{
    SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                      , spdlog::level::trace
                      , "Loading configuration for color space conversion service..." );
    this->improc::BaseService<KeyType,ContextType>::Load(service_json);

    for (Json::Value::const_iterator service_json_iter = service_json.begin(); service_json_iter != service_json.end(); ++service_json_iter)
    {
        const std::string kFromColorSpaceKey = "from_color_space";
        const std::string kToColorSpaceKey   = "to_color_space";

        SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                          , spdlog::level::info
                          , "Analyzing field {} for color space service...",service_json_iter.name() );
        if (service_json_iter.name() == kFromColorSpaceKey)
        {
            this->from_color_space_ = service_json_iter->asString();
        }
        else if (service_json_iter.name() == kToColorSpaceKey)
        {
            if (service_json_iter->isArray() == true)
            {
                for (Json::Value::const_iterator array_iter = service_json_iter->begin(); array_iter != service_json_iter->end(); ++array_iter)
                {
                    this->to_color_space_.push_back(array_iter->asString());
                }
            }
            else
            {
                this->to_color_space_.push_back(service_json_iter->asString());
            }
        }
    }

    if (this->to_color_space_.empty() == true)
    {
        SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                          , spdlog::level::err
                          , "ERROR_01: To color space field missing." );
        throw improc::file_processing_error();
    }
    return (*this);
}

template <typename KeyType,typename ContextType>
void improc::ConvertColorSpace<KeyType,ContextType>::Run(improc::Context<KeyType,ContextType>& context) const
{
    SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                      , spdlog::level::trace
                      , "Running color space conversion service..." );
    improc::ColorSpaceImage image {};
    image.set_data(std::any_cast<cv::Mat>(context.Get(this->inputs_[improc::ConvertColorSpace<KeyType,ContextType>::kImageDataKeyIndex])));
    if (this->from_color_space_.has_value() == true)
    {
        image.set_color_space(this->from_color_space_.value());
    }
    else
    {
        image.set_color_space(std::any_cast<improc::ColorSpace>(context.Get(this->inputs_[improc::ConvertColorSpace<KeyType,ContextType>::kColorSpaceKeyIndex])));
    }

    for (size_t to_color_space_idx = 0; to_color_space_idx < this->to_color_space_.size(); ++to_color_space_idx)
    {
        image.ConvertToColorSpace(this->to_color_space_[to_color_space_idx]);
    }
    context[this->outputs_[0]] = image;
}