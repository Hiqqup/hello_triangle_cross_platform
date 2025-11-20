//
// Created by ju on 11/19/25.
//

#include "DesktopBackend.h"
#include "gl_backend.h"
#include <GLFW/glfw3.h>
#include <iostream>


GLFWwindow* window ;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}





void DesktopBackend::initialize_context() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return ;
    }

    // Request an OpenGL ES 3.0 context
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

     window = glfwCreateWindow(800, 600, "Hello Triangle GLES 3.0", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return ;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize GLAD for GLES
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return ;
    }
}



std::filesystem::path DesktopBackend::resolveAssetPath(const std::filesystem::path &relativeAssetPath) {
    auto mergedPath = ("./assets" / relativeAssetPath).make_preferred();
    return std::filesystem::canonical(mergedPath);
}

void DesktopBackend::do_main_loop() {
    while(!glfwWindowShouldClose(window)) {
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void DesktopBackend::cleanup() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
}
