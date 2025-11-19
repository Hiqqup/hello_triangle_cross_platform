//
// Created by ju on 11/19/25.
//

#pragma once
#include "IBackend.h"


class DesktopBackend: public IBackend {
public:
    void init() override;
    void do_main_loop() override;
    void cleanup() override;
};
