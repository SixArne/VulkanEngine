#include "ImageLoader.h"
#include "core/logger/Log.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

std::shared_ptr<Image> ImageLoader::Load(const char *path)
{
    int width, height, channels;
    unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
    if (!data) {
        F_LOG_CORE_ERROR("Failed to load image: {0}", path);
        return nullptr;
    }

    auto image = std::shared_ptr<Image>(new Image{width, height, channels, data}, Image());
    return image;
}