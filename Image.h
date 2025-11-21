//
// Created by ju on 11/20/25.
//

#pragma once

#include <filesystem>

class Image {
    public:
    explicit  Image(const std::filesystem::path &full_image_path) ;
    ~Image();
    unsigned char * data;
    int width{};
    int height{};
};
