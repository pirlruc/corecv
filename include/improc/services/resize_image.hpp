#ifndef IMPROC_SERVICES_RESIZE_IMAGE_HPP
#define IMPROC_SERVICES_RESIZE_IMAGE_HPP

#include <improc/improc_defs.hpp>
#include <improc/corecv/logger_improc.hpp>
#include <improc/corecv/image.hpp>
#include <improc/corecv/interpolation_type.hpp>
#include <improc/services/base_service.hpp>

namespace improc {
    // TODO: Review implementation and add tests
    template <typename KeyType,typename ContextType>
    class IMPROC_API Resize : public improc::BaseService<KeyType,ContextType>
    {
        private:
            static constexpr unsigned int   kImageDataKeyIndex   = 0;
            static constexpr unsigned int   kToImageSizeKeyIndex = 1;
            
            std::optional<cv::Size>         to_image_size_;
            std::optional<cv::Size2d>       scaling_;
            InterpolationType               interpolation_;

        public:
            Resize();

            void                            Load(const Json::Value& service_json)                       override;
            void                            Run (improc::Context<KeyType,ContextType>& context) const   override;
    };

    typedef Resize<std::string,std::any>    StringKeyHeterogeneousResize;
}

#include <improc/services/resize_image.tpp>

#endif