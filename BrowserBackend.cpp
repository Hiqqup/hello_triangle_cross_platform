//
// Created by ju on 11/19/25.
//

#include "BrowserBackend.h"
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include <GLES3/gl3.h>
#include <iostream>



void updateViewport() {
    double width, height;
    emscripten_get_element_css_size("#canvas", &width, &height);

    // Set the canvas internal size to match CSS size
    emscripten_set_canvas_element_size("#canvas", (int)width, (int)height);

    glViewport(0, 0, (int)width, (int)height);
}

GLuint shaderProgram;
GLuint VAO;

// Vertex shader (WebGL2 = GLES 3.0)
const char* vertexShaderSource =
"#version 300 es\n"
"layout(location = 0) in vec3 aPos;\n"
"layout(location = 1) in vec3 aColor;\n"
"out vec3 vertexColor;\n"
"void main() {\n"
"    gl_Position = vec4(aPos, 1.0);\n"
"    vertexColor = aColor;\n"
"}\n";

// Fragment shader
const char* fragmentShaderSource =
"#version 300 es\n"
"precision mediump float;\n"
"in vec3 vertexColor;\n"
"out vec4 FragColor;\n"
"void main() {\n"
"    FragColor = vec4(vertexColor, 1.0);\n"
"}\n";


void BrowserBackend::init() {
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

    std::cout << "WebGL2 / GLES 3.0 initialized\n";
}
void render()
{

    updateViewport();   // <--

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
void BrowserBackend::do_main_loop() {
    emscripten_set_main_loop(render, 0, true);
}

void BrowserBackend::cleanup() {
}
