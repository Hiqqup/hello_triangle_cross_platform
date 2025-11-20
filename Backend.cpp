//
// Created by ju on 11/19/25.
//
#include "Backend.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "Image.h"


std::string Backend::readText(const std::filesystem::path &filePath) {
    std::ifstream sourceFile(resolveAssetPath(filePath));
    if (!sourceFile.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
    }
    std::stringstream buffer;
    buffer << sourceFile.rdbuf();
    return buffer.str();
}

void handle_shader_compilation_error(const GLuint shaderID) {
    GLint success = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

    if (!success) {
        GLint logLength = 0;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);

        std::string infoLog;
        infoLog.resize(logLength);

        glGetShaderInfoLog(shaderID, logLength, nullptr, infoLog.data());

        // Clean up the failed shader
        glDeleteShader(shaderID);

        // You can throw, log, or return 0 depending on your design.
        throw std::runtime_error(
            "Shader compile error:\n" + infoLog
        );
    }
}
 GLuint Backend::loadAndCompileShader(GLuint shaderType, const std::filesystem::path &shaderPath) {
     auto shaderSource = readText(shaderPath);
     auto source = shaderSource.c_str();
     auto shaderID = glCreateShader(shaderType);
     glShaderSource(shaderID, 1, &source, nullptr);
     glCompileShader(shaderID);
    handle_shader_compilation_error(shaderID);

    return shaderID;
 }



void Backend::init() {


    GLuint vertexShader = loadAndCompileShader(GL_VERTEX_SHADER, "shader.vert");
    GLuint fragmentShader =loadAndCompileShader(GL_FRAGMENT_SHADER, "shader.frag");

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Triangle vertex data
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };

unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    Image i = Image(resolveAssetPath("container.jpg"));
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, i.width, i.height, 0, GL_RGB, GL_UNSIGNED_BYTE, i.data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 0);
}



void Backend::render() {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
