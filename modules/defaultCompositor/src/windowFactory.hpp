//
// Created by fifthzoner on 16/10/2025.
//

#ifndef UNTITLED_EDITOR_WINDOW_FACTORY_HPP
#define UNTITLED_EDITOR_WINDOW_FACTORY_HPP

#include <expected>
#include <string>

#include "../../../src/misc/vec2.tpp"
#include "window.hpp"

class WindowFactory {
    Vec2i _size;
    std::string _name{};
    SDL_WindowFlags _flags{};

    WindowFactory() = default;

public:
    /// \brief Creates a new window factory
    /// \return factory
    [[nodiscard]] static WindowFactory New();
    /// \brief Creates the window using the factory object
    /// \return newly created window or an error
    [[nodiscard]] std::expected<Window, Error> Create();

    /// \brief Sets window size
    /// \param size size
    /// \return factory
    [[nodiscard]] WindowFactory setSize(Vec2i&& size);
    /// \brief Sets window size
    /// \param size size
    /// \return factory
    [[nodiscard]] WindowFactory setSize(const Vec2i& size);
    /// \brief Sets window name
    /// \param name name to set
    /// \return factory
    [[nodiscard]] WindowFactory setName(std::string&& name);
    /// \brief Sets window name
    /// \param name name to set
    /// \return factory
    [[nodiscard]] WindowFactory setName(const std::string& name);

    /// \brief Sets parameter, as described in SDL header: window is in fullscreen mode
    /// \return factory
    [[nodiscard]] WindowFactory setFullscreen();
    /// \brief Sets parameter, as described in SDL header: window usable with OpenGL context
    /// \return factory
    [[nodiscard]] WindowFactory setOpenGL();
    /// \brief Sets parameter, as described in SDL header: window is occluded
    /// \return factory
    [[nodiscard]] WindowFactory setOccluded();
    /// \brief Sets parameter, as described in SDL header: window is neither mapped onto the desktop nor shown in the taskbar/dock/window list; SDL_ShowWindow() is required for it to become visible
    /// \return factory
    [[nodiscard]] WindowFactory setHidden();
    /// \brief Sets parameter, as described in SDL header: no window decoration
    /// \return factory
    [[nodiscard]] WindowFactory setBorderless();
    /// \brief Sets parameter, as described in SDL header: window can be resized
    /// \return factory
    [[nodiscard]] WindowFactory setResizable();
    /// \brief Sets parameter, as described in SDL header: window is minimized
    /// \return factory
    [[nodiscard]] WindowFactory setMinimized();
    /// \brief Sets parameter, as described in SDL header: window is maximized
    /// \return factory
    [[nodiscard]] WindowFactory setMaximized();
    /// \brief Sets parameter, as described in SDL header: window has grabbed mouse input
    /// \return factory
    [[nodiscard]] WindowFactory setMouseGrabbed();
    /// \brief Sets parameter, as described in SDL header: window has input focus
    /// \return factory
    [[nodiscard]] WindowFactory setInputFocus();
    /// \brief Sets parameter, as described in SDL header: window has mouse focus
    /// \return factory
    [[nodiscard]] WindowFactory setMouseFocus();
    /// \brief Sets parameter, as described in SDL header: window not created by SDL
    /// \return factory
    [[nodiscard]] WindowFactory setExternal();
    /// \brief Sets parameter, as described in SDL header: window is modal
    /// \return factory
    [[nodiscard]] WindowFactory setModal();
    /// \brief Sets parameter, as described in SDL header: window uses high pixel density back buffer if possible
    /// \return factory
    [[nodiscard]] WindowFactory setHighPixelDensity();
    /// \brief Sets parameter, as described in SDL header: window has mouse captured (unrelated to MOUSE_GRABBED)
    /// \return factory
    [[nodiscard]] WindowFactory setMouseCapture();
    /// \brief Sets parameter, as described in SDL header: window has relative mode enabled
    /// \return factory
    [[nodiscard]] WindowFactory setMouseRelativeMode();
    /// \brief Sets parameter, as described in SDL header: window should always be above others
    /// \return factory
    [[nodiscard]] WindowFactory setAlwaysOnTop();
    /// \brief Sets parameter, as described in SDL header: window should be treated as a utility window, not showing in the task bar and window list
    /// \return factory
    [[nodiscard]] WindowFactory setUtility();
    /// \brief Sets parameter, as described in SDL header: window should be treated as a tooltip and does not get mouse or keyboard focus, requires a parent window
    /// \return factory
    [[nodiscard]] WindowFactory setTooltip();
    /// \brief Sets parameter, as described in SDL header: window should be treated as a popup menu, requires a parent window
    /// \return factory
    [[nodiscard]] WindowFactory setPopupMenu();
    /// \brief Sets parameter, as described in SDL header: window has grabbed keyboard input
    /// \return factory
    [[nodiscard]] WindowFactory setKeyboardGrabbed();
    /// \brief Sets parameter, as described in SDL header: window usable for Vulkan surface
    /// \return factory
    [[nodiscard]] WindowFactory setVulkan();
    /// \brief Sets parameter, as described in SDL header: window usable for Metal view
    /// \return factory
    [[nodiscard]] WindowFactory setMetal();
    /// \brief Sets parameter, as described in SDL header: window with transparent buffer
    /// \return factory
    [[nodiscard]] WindowFactory setTransparent();
    /// \brief Sets parameter, as described in SDL header: window should not be focusable
    /// \return factory
    [[nodiscard]] WindowFactory setNotFocusable();
};


#endif //UNTITLED_EDITOR_WINDOW_FACTORY_HPP