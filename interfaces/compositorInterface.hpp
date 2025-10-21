//
// Created by fifthzoner on 19/10/2025.
//

#ifndef UNTITLED_EDITOR_COMPOSITOR_INTERFACE_HPP
#define UNTITLED_EDITOR_COMPOSITOR_INTERFACE_HPP

#include "../untitledEditor.hpp"

// the composer is responsible for the main loop, handling events, windows and editors

#define COMPOSITOR_INTERFACE_VERSION 1

INTERFACE(Compositor,
    INTERFACE_FUNCTION(std::optional<Error>, MainLoop, Settings&, settings, TaskManager&, manager)
    )

#endif //UNTITLED_EDITOR_COMPOSITOR_INTERFACE_HPP