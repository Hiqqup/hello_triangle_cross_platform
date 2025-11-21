//
// Created by ju on 11/19/25.
//

#pragma once
#include <filesystem>
// ReSharper disable once CppUnusedIncludeDirective
#include "../gl_backend.h"
#include <GLFW/glfw3.h>
#include <functional>

class Context {
    public:
        GLFWwindow* window ;
        Context();
        ~Context();
    };
class Platform {
public:
    Context context;
    virtual ~Platform() = default;
    virtual void do_main_loop(const std::function<void()>& callback) = 0;
    virtual std::filesystem::path resolveAssetPath(const std::filesystem::path &relativeAssetPath) = 0 ;
};
extern Platform* global_backend;