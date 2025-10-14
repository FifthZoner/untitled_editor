//
// Created by fifthzoner on 12/10/2025.
//

#ifndef UNTITLED_EDITOR_MODULE_MANAGER_HPP
#define UNTITLED_EDITOR_MODULE_MANAGER_HPP

#include <optional>

#include "../options.hpp"
#include "../errors/errors.hpp"

std::optional<Error> InitializeModuleManager(const Options& options);

#endif //UNTITLED_EDITOR_MODULE_MANAGER_HPP