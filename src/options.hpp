//
// Created by fifthzoner on 12/10/2025.
//

#ifndef UNTITLED_EDITOR_OPTIONS_HPP
#define UNTITLED_EDITOR_OPTIONS_HPP

#include <string>
#include <vector>
#include <cstdint>

struct Options {
    // general stuff
    std::string executablePath{};
    std::vector<std::string> modulePaths{};

    uint32_t taskRunnerAmount = 32;

    bool overrideModulesPath = false;
};

#endif //UNTITLED_EDITOR_OPTIONS_HPP