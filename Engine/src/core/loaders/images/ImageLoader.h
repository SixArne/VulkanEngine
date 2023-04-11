#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include <memory>

#include "core/Singleton.h"
#include <stb_image.h>
#include "core/logger/Log.h"

struct Image
{
    int width;
    int height;
    int channels;
    unsigned char* data;

    Image() : width(0), height(0), channels(0), data(nullptr) {}
    Image(int w, int h, int c, unsigned char* d)
        : width(w), height(h), channels(c), data(d) {}

    void operator()(Image* img)
    {
        stbi_image_free(img->data);
        F_LOG_CORE_DEBUG("Image freed");
    }
};

class ImageLoader : public Singleton<ImageLoader>
{
public:
    std::shared_ptr<Image> Load(const char* path);

private:
    friend class Singleton<ImageLoader>;
    ImageLoader() = default;
};


#endif // IMAGE_LOADER_H