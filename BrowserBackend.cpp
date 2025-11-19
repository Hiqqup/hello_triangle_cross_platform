//
// Created by ju on 11/19/25.
//

#include "BrowserBackend.h"
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include "gl_backend.h"
#include <iostream>



void updateViewport() {
    double width, height;
    emscripten_get_element_css_size("#canvas", &width, &height);

    // Set the canvas internal size to match CSS size
    emscripten_set_canvas_element_size("#canvas", (int)width, (int)height);

    glViewport(0, 0, (int)width, (int)height);
}

std::filesystem::path BrowserBackend::resolveAssetPath(const std::filesystem::path &relativeAssetPath) {
    return std::filesystem::path("/assets") / relativeAssetPath;
}

void BrowserBackend::initialize_context() {
    EmscriptenWebGLContextAttributes attr;
    emscripten_webgl_init_context_attributes(&attr);

    attr.alpha = false;
    attr.depth = true;
    attr.stencil = false;
    attr.antialias = false;
    attr.majorVersion = 2;
    attr.minorVersion = 0;

    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx =
        emscripten_webgl_create_context("#canvas", &attr);

    if (ctx <= 0) {
        std::cerr << "Failed to create WebGL2 context\n";
        return;
    }

    emscripten_webgl_make_context_current(ctx);
}
void render_thunk(void* arg) {
    updateViewport();
    static_cast<BrowserBackend*>(arg)->render();
}
void BrowserBackend::do_main_loop() {
    emscripten_set_main_loop_arg(render_thunk,this, 0, true);
}

void BrowserBackend::cleanup() {
}
