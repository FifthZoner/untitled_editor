//
// Created by fifthzoner on 19/10/2025.
//

#ifndef UNTITLED_EDITOR_UNTITLED_EDITOR_HPP
#define UNTITLED_EDITOR_UNTITLED_EDITOR_HPP

// this header contains things that will be needed by modules

// includes
#include "src/definitions.hpp"
#include "src/settings.hpp"
#include "src/errors/errors.hpp"
#include "src/misc/vec2.tpp"
#include "src/taskManager/taskManager.hpp"
#include "src/moduleManager/moduleManager.tpp"
#include "interfaces/interfaceMacro.hpp"

// export macro
#ifdef TARGET_WINDOWS
    #define EXPORT_ATTRIBUTE __declspec(dllexport)
#elif defined(TARGET_UNIX) or defined(TARGET_LINUX)
    #define EXPORT_ATTRIBUTE __attribute__((visibility("default")))
#else
    #error Unsupported export interface target!
#endif

#endif //UNTITLED_EDITOR_UNTITLED_EDITOR_HPP