//
// Created by fifthzoner on 12/10/2025.
//

#ifndef UNTITLED_EDITOR_STARTUP_HPP
#define UNTITLED_EDITOR_STARTUP_HPP

#include <expected>

#include "../settings.hpp"
#include "../errors/errors.hpp"

/// <summary>
/// Takes the command line arguments and prepares anything
/// </summary>
/// <param name="argc">main's argc, amount of parameters</param>
/// <param name="argv">main's argv, array of parameters</param>
/// <returns>Initial options object</returns>
[[nodiscard]] std::expected<Settings, Error> LoadOptions(int argc, char** argv);

#endif //UNTITLED_EDITOR_STARTUP_HPP