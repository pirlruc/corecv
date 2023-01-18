template <typename KeyType,typename ContextType>
improc::Resize<KeyType,ContextType>::Resize()   : improc::BaseService<KeyType,ContextType>()
                                                , to_image_size_(std::optional<cv::Size>())
                                                , scale_(std::optional<cv::Size2d>())
                                                , interpolation_(improc::Interpolation:Type::kLinear)
{}

template <typename KeyType,typename ContextType>
void improc::Resize<KeyType,ContextType>::Load(const Json::Value& service_json)
{
    SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                      , spdlog::level::trace
                      , "Loading configuration for image resize service..." );
    this->improc::BaseService<KeyType,ContextType>::Load(service_json);

    for (Json::Value::const_iterator service_json_iter = service_json.begin(); service_json_iter != service_json.end(); ++service_json_iter)
    {
        const std::string kInterpolationKey = "interpolation";
        const std::string kToImageSizeKey   = "to_image_size";
        const std::string kScaleKey         = "scale";
        const std::string kWidthKey         = "width";
        const std::string kHeightKey        = "height";

        SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                          , spdlog::level::info
                          , "Analyzing field {} for image resize service...",service_json_iter.name() );
        if (service_json_iter.name() == kInterpolationKey)
        {
            this->interpolation_ = service_json_iter->asString();
        }
        else if (service_json_iter.name() == kToImageSizeKey)
        {
            for (Json::Value::const_iterator field_iter = service_json_iter->begin(); field_iter != service_json_iter->end(); ++field_iter)
            {
                SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                                , spdlog::level::info
                                , "Analyzing field {} for image size...",service_json_iter.name() );
                if      (field_iter.name() == kWidth)   this->to_image_size_.width  = field_iter->asUInt();
                else if (field_iter.name() == kHeight)  this->to_image_size_.height = field_iter->asUInt();
            }
        }
        else if (service_json_iter.name() == kScaleKey)
        {
            for (Json::Value::const_iterator field_iter = service_json_iter->begin(); field_iter != service_json_iter->end(); ++field_iter)
            {
                SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                                , spdlog::level::info
                                , "Analyzing field {} for image size...",service_json_iter.name() );
                if      (field_iter.name() == kWidth)   this->scaling_.width  = field_iter->asDouble();
                else if (field_iter.name() == kHeight)  this->scaling_.height = field_iter->asDouble();
            }
        }
    }

    if (this->to_image_size_.has_value() == false && this->scaling_.has_value() == false)
    {
        SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                          , spdlog::level::err
                          , "ERROR_01: Target image size information missing." );
        throw improc::file_processing_error();
    }

    if (this->to_image_size_.has_value() == true && this->scaling_.has_value() == true)
    {
        SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                          , spdlog::level::err
                          , "ERROR_02: Scaling and target image size provided. Only one can be provided" );
        throw improc::file_processing_error();
    }
}

template <typename KeyType,typename ContextType>
void improc::Resize<KeyType,ContextType>::Run(improc::Context<KeyType,ContextType>& context) const
{
    SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                      , spdlog::level::trace
                      , "Running image resize service..." );
    improc::Image image {};
    image.set_data(std::any_cast<cv::Mat>(context.Get(this->inputs_[improc::Resize<KeyType,ContextType>::kImageDataKeyIndex])));
    if (this->to_image_size_.has_value() == true)
    {
        image.Resize(this->to_image_size_.value(),this->interpolation_);
    }
    else
    {
        image.Resize(this->scaling_.value(),this->interpolation_);
    }
    context[this->outputs_[0]] = image;
}