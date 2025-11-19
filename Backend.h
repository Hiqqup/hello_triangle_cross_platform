//
// Created by ju on 11/19/25.
//

#pragma once
#include "gl_backend.h"



class Backend {
public:

    GLuint shaderProgram;
    GLuint VAO, VBO;
    virtual void initialize_context() = 0;
    void init() ;
    void render();
    virtual void do_main_loop() = 0;
    virtual void cleanup() = 0;
};
