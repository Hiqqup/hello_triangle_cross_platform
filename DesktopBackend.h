//
// Created by ju on 11/19/25.
//

#pragma once
#include "Backend.h"


class DesktopBackend: public Backend {
public:
    void initialize_context() override;
    std::filesystem::path resolveAssetPath(const std::filesystem::path &relativeAssetPath) override;
    void do_main_loop() override;
    void cleanup() override;
};
