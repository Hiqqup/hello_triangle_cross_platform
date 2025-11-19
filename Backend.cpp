//
// Created by ju on 11/19/25.
//
#include "Backend.h"

#include <fstream>
#include <iostream>
#include <sstream>

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





std::string Backend::readText(const std::filesystem::path &filePath) {
    std::ifstream sourceFile(resolveAssetPath(filePath));
    if (!sourceFile.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
    }
    std::stringstream buffer;
    buffer << sourceFile.rdbuf();
    return buffer.str();
}

 GLuint Backend::loadAndCompileShader(GLuint shaderType, const std::filesystem::path &shaderPath) {
     auto shaderSource = readText(shaderPath);
     auto source = shaderSource.c_str();
     auto shaderID = glCreateShader(shaderType);
     glShaderSource(shaderID, 1, &source, nullptr);
     glCompileShader(shaderID);
    return shaderID;
 }

void Backend::init() {


    GLuint vertexShader = loadAndCompileShader(GL_VERTEX_SHADER, "shader.vert");
    GLuint fragmentShader =loadAndCompileShader(GL_FRAGMENT_SHADER, "shader.frag");
//
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

void Backend::render() {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
}
