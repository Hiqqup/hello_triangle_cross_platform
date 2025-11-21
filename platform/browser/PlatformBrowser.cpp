//
// Created by ju on 11/19/25.
//

#include "PlatformBrowser.h"
#include <emscripten/emscripten.h>



std::filesystem::path PlatformBrowser::resolveAssetPath(const std::filesystem::path &relativeAssetPath) {
    return std::filesystem::path("/assets") / relativeAssetPath;
}


void PlatformBrowser::do_main_loop(const std::function<void()>& callback) {
    emscripten_set_main_loop_arg([](void* arg) {
            const auto* func = static_cast<std::function<void()> *>(arg);
            (*func)();
            // ReSharper disable once CppCStyleCast
    }, (void*)&callback, 0, true);
}
