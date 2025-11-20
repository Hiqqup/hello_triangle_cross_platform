//
// Created by ju on 11/19/25.
//

#pragma once
#include "gl_backend.h"
#include <filesystem>





class Backend {
public:


    virtual std::filesystem::path resolveAssetPath(const std::filesystem::path &relativeAssetPath) = 0 ;
    virtual std::string readText(const std::filesystem::path &filePath);
    virtual GLuint loadAndCompileShader(GLuint shaderType, const std::filesystem::path &shaderPath);

    GLuint shaderProgram;
    GLuint texture;
    GLuint VAO, VBO, EBO;
    virtual void initialize_context() = 0;
    virtual void init() ;
    virtual void render();
    virtual void do_main_loop() = 0;
    virtual void cleanup() = 0;
};
