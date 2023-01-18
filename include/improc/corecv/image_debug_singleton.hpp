#ifndef IMPROC_CORECV_IMAGE_DEBUG_SINGLETON_H
#define IMPROC_CORECV_IMAGE_DEBUG_SINGLETON_H

#include <improc/improc_defs.h>
#include <improc/corecv/image.h>

namespace improc {
    // TODO: Review implementation and add tests
    /**
     * @brief Singleton template for image debugging
     * 
     * @tparam type 
     */
    template <typename type>
    class IMPROC_API ImageDebugSingleton
    {
        public:
            struct DebugImage
            {
                Image                           image;
                std::string                     filepath;
            };
            
        private:
            DebugImage                          data_;
            std::vector<DebugImage>             history_;

        protected:
            ImageDebugSingleton();
            
        public:
            ImageDebugSingleton(ImageDebugSingleton&   that) = delete;
            ImageDebugSingleton(ImageDebugSingleton&&  that) = delete;
            void operator=(const ImageDebugSingleton&  that) = delete;
            void operator=(const ImageDebugSingleton&& that) = delete;

            static ImageDebugSingleton          get();

            DebugImage                          data()     const;
            void                                set_data(const DebugImage& image);
            void                                Revert();
            void                                Clear();
    };
}

#include <improc/corecv/image_debug_singleton.tpp>

#endif