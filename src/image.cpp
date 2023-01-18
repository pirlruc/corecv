#include <improc/corecv/image.hpp>

improc::Image::Image() : data_(cv::Mat()) {}

improc::Image::Image(const cv::Mat& image_data) : Image()
{
    SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                      , spdlog::level::trace
                      , "Creating image object..." );    
    this->set_data(image_data);
}

void improc::Image::set_data(const cv::Mat& image_data)
{
    SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                      , spdlog::level::trace
                      , "Setting image data..." );
    if (image_data.depth() != CV_8U) 
    {
        SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                          , spdlog::level::err
                          , "ERROR_01: Not supported data type for image. Expected {} received {}."
                          , CV_8U, image_data.depth() );
        throw improc::not_supported_data_type();
    }
    this->data_ = image_data;
}

cv::Mat improc::Image::get_data() const
{
    SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                      , spdlog::level::trace
                      , "Obtaining image data..." );    
    return this->data_;
}

improc::Image improc::Image::Clone() const
{
    SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                      , spdlog::level::trace
                      , "Cloning image object..." );    
    return improc::Image(this->get_data().clone());
}


// void improc::Image::Resize(const cv::Size& to_image_size, const InterpolationType& interpolation);
// {
//     SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
//                       , spdlog::level::trace
//                       , "Resizing image using size..." );
//     if (this->data_.size() == image_size)
//     {
//         SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
//                           , spdlog::level::debug
//                           , "Resizing not performed. Image already has target size." );
//     }
//     else
//     {
//         cv::resize(this->data_,this->data_,to_image_size,0,0,interpolation.ToOpenCV());
//     }
// }

// void improc::Image::Resize(const cv::Size2d& scaling, const InterpolationType& interpolation);
// {
//     SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
//                       , spdlog::level::trace
//                       , "Resizing image using scale..." );
//     if (scaling.width == 1.0 && scaling.height == 1.0)
//     {
//         SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
//                           , spdlog::level::debug
//                           , "Resizing not performed. Image already has target size." );
//     }
//     else
//     {
//         cv::resize(this->data_,this->data_,cv::Size(),scaling.width,scaling.height,interpolation.ToOpenCV());
//     }
// }

improc::ColorSpaceImage::ColorSpaceImage() : improc::Image()
                                           , color_space_(improc::ColorSpace::kRGB) {}

improc::ColorSpaceImage::ColorSpaceImage(const cv::Mat& image_data , const improc::ColorSpace& color_space) : Image(image_data)
{
    SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                      , spdlog::level::trace
                      , "Creating color space image object..." );    
    this->set_color_space(color_space);
}

void improc::ColorSpaceImage::set_color_space(const improc::ColorSpace& color_space)
{
    SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                      , spdlog::level::trace
                      , "Setting color space..." );
    if (this->data_.channels() != color_space.GetNumberChannels())
    {
        SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                          , spdlog::level::err
                          , "ERROR_01: Invalid color space for image. Expected {} channels but image has {}."
                          , color_space.GetNumberChannels(), this->data_.channels() );
        throw improc::invalid_color_space();
    }
    this->color_space_ = color_space;
}

improc::ColorSpace improc::ColorSpaceImage::get_color_space() const
{
    SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                      , spdlog::level::trace
                      , "Obtaining color space..." );    
    return this->color_space_;
}

improc::ColorSpaceImage improc::ColorSpaceImage::Clone() const
{
    SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                      , spdlog::level::trace
                      , "Cloning color space image object..." );    
    return improc::ColorSpaceImage(this->Image::Clone().get_data(),this->color_space_);
}

void improc::ColorSpaceImage::ConvertToColorSpace(const improc::ColorSpace& to_color_space)
{
    SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                      , spdlog::level::trace
                      , "Converting color space image from {} to {}..."
                      , this->color_space_.ToString(), to_color_space.ToString() );
    if (this->color_space_ == to_color_space)
    {
        SPDLOG_LOGGER_CALL( improc::ImageProcLogger::get()->data()
                          , spdlog::level::debug
                          , "Color conversion not performed. Image is already in target color space." );
    }
    else
    {
        cv::cvtColor(this->data_,this->data_,this->color_space_.GetColorConversionCode(to_color_space));
        this->color_space_ = to_color_space;
    }
}
