//
// Created by ju on 11/19/25.
//

#pragma once
#include "Backend.h"


class BrowserBackend: public Backend {
public:
    std::filesystem::path resolveAssetPath(const std::filesystem::path &relativeAssetPath) override;

    void initialize_context() override;
    //void init() override;
    void do_main_loop() override;
    void cleanup() override;
};
