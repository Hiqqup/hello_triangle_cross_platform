//
// Created by ju on 11/20/25.
//

#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <stb_image.h>

Image::Image(const std::filesystem::path &full_image_path) {
    int  nrChannels;
    const std::filesystem::path path = full_image_path;
    const char* texture_path = path.c_str();
    data = stbi_load(texture_path, &width, &height, &nrChannels, 0);
    if (!data) {
        std::cerr << "Failed to load image";
    }
}

Image::~Image() {
    stbi_image_free(data);
}
