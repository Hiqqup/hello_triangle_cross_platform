//
// Created by ju on 11/19/25.
//

#pragma once
#include "Backend.h"


class DesktopBackend final : public Backend {
public:
    DesktopBackend();
    void do_main_loop(const std::function<void()> &func) override;
    std::filesystem::path resolveAssetPath(const std::filesystem::path &relativeAssetPath) override;
};
