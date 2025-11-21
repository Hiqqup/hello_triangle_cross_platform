//
// Created by ju on 11/19/25.
//

#include "DesktopBackend.h"
#include <iostream>


std::filesystem::path DesktopBackend::resolveAssetPath(const std::filesystem::path &relativeAssetPath) {
    auto mergedPath = ("./assets" / relativeAssetPath).make_preferred();
    return std::filesystem::canonical(mergedPath);
}



void DesktopBackend::do_main_loop(const std::function<void()>& func) {
    while(!glfwWindowShouldClose(global_backend->context.window)) {
        func();
    }
}

DesktopBackend::DesktopBackend() {
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "Failed to initialize GLAD\n";
    }
}
