//
// Created by ju on 11/19/25.
//

#pragma once
#include "Backend.h"


class BrowserBackend final: public Backend {
public:
    void do_main_loop(const std::function<void()> &callback) override;
    std::filesystem::path resolveAssetPath(const std::filesystem::path &relativeAssetPath) override;
};
