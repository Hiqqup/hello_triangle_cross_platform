//
// Created by ju on 11/19/25.
//

#pragma once


class IBackend {
public:
    virtual void init() = 0;
    virtual void do_main_loop() = 0;
    virtual void cleanup() = 0;
};