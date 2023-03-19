#include <improc/corecv/image.hpp>

improc::Image::Image() : data_(cv::Mat()) {}

improc::Image::Image(const cv::Mat& image_data) : Image()
{
    IMPROC_CORECV_LOGGER_TRACE("Creating image object...");    
    this->set_data(image_data);
}

void improc::Image::set_data(const cv::Mat& image_data)
{
    IMPROC_CORECV_LOGGER_TRACE("Setting image data...");
    if (image_data.depth() != CV_8U) 
    {
        IMPROC_CORECV_LOGGER_ERROR  ( "ERROR_01: Not supported data type for image. Expected {} received {}."
                                    , CV_8U, image_data.depth() );
        throw improc::not_supported_data_type();
    }
    this->data_ = image_data;
}

cv::Mat improc::Image::get_data() const
{
    IMPROC_CORECV_LOGGER_TRACE("Obtaining image data...");    
    return this->data_;
}

improc::Image improc::Image::Clone() const
{
    IMPROC_CORECV_LOGGER_TRACE("Cloning image object...");    
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

improc::ColorSpace improc::ColorSpaceImage::get_color_space() const
{
    IMPROC_CORECV_LOGGER_TRACE("Obtaining color space...");    
    return this->color_space_;
}

improc::ColorSpaceImage improc::ColorSpaceImage::Clone() const
{
    IMPROC_CORECV_LOGGER_TRACE("Cloning color space image object...");    
    return improc::ColorSpaceImage(this->Image::Clone().get_data(),this->color_space_);
}
