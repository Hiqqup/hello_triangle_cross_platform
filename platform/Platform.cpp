//
// Created by ju on 11/19/25.
//
#include "Platform.h"

#include <fstream>
#include <iostream>




void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
}

Context::Context() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return ;
    }

    // Request an OpenGL ES 3.0 context
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

     window = glfwCreateWindow(800, 600, "Cross Platform Game Engine", nullptr, nullptr);
    if (!window ) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return ;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}


Context::~Context() {
    glfwDestroyWindow(window);
    glfwTerminate();
}
