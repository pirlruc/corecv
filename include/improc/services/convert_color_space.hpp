#ifndef IMPROC_SERVICES_CONVERT_COLOR_SPACE_HPP
#define IMPROC_SERVICES_CONVERT_COLOR_SPACE_HPP

#include <improc/improc_defs.hpp>
#include <improc/corecv/logger_improc.hpp>
#include <improc/corecv/structures/color_space.hpp>
#include <improc/corecv/image.hpp>
#include <improc/services/base_service.hpp>

namespace improc {
    // TODO: Review implementation and add tests
    template <typename KeyType,typename ContextType>
    class IMPROC_API ConvertColorSpace : public improc::BaseService<KeyType,ContextType>
    {
        private:
            static constexpr unsigned int   kImageDataKeyIndex  = 0;
            static constexpr unsigned int   kColorSpaceKeyIndex = 1;
            
            std::optional<ColorSpace>       from_color_space_;
            std::vector<ColorSpace>         to_color_space_;

        public:
            ConvertColorSpace();

            ConvertColorSpace&              Load(const Json::Value& service_json)                       override;
            void                            Run (improc::Context<KeyType,ContextType>& context) const   override;
    };

    typedef ConvertColorSpace<std::string,std::any> StringKeyHeterogeneousConvertColorSpace;
}

#include <improc/services/convert_color_space.tpp>

#endif