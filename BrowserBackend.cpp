//
// Created by ju on 11/19/25.
//

#include "BrowserBackend.h"
#include <emscripten/emscripten.h>



std::filesystem::path BrowserBackend::resolveAssetPath(const std::filesystem::path &relativeAssetPath) {
    return std::filesystem::path("/assets") / relativeAssetPath;
}


void BrowserBackend::do_main_loop(const std::function<void()>& callback) {
    emscripten_set_main_loop_arg([](void* arg) {
            const auto* func = static_cast<std::function<void()> *>(arg);
            (*func)();
            // ReSharper disable once CppCStyleCast
    }, (void*)&callback, 0, true);
}
