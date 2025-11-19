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

/*
void BrowserBackend::init() {

    // Compile vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // Compile fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // Link shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Triangle vertex data
    float vertices[] = {
        // positions         // colors
         0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f
    };

    GLuint VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

}
*/
void BrowserBackend::render()
{

    updateViewport();   // <--

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
void render_thunk(void* arg) {
    static_cast<BrowserBackend*>(arg)->render();
}
void BrowserBackend::do_main_loop() {
    emscripten_set_main_loop_arg(render_thunk,this, 0, true);
}

void BrowserBackend::cleanup() {
}
