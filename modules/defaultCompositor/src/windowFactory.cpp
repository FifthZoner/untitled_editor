//
// Created by fifthzoner on 16/10/2025.
//

#include "windowFactory.hpp"

#include "../../../src/errors/errors.hpp"

WindowFactory WindowFactory::New() {
    return {};
}

std::expected<Window, Error> WindowFactory::Create() {
    Window window{};
    window.title = std::make_unique<char>(_name.size() + 1);
    strncpy(window.title.get(), _name.c_str(), _name.size() + 1);
    window.window = SDL_CreateWindow(window.title.get(), _size.x, _size.y, _flags);
    TrueOrUnexpected(window.window != nullptr, std::string("Window creation failed: ") + SDL_GetError());
    return std::move(window);
}

WindowFactory WindowFactory::setSize(Vec2i&& size) {
    this->_size = size;
    return *this;
}

WindowFactory WindowFactory::setSize(const Vec2i& size) {
    this->_size = size;
    return *this;
}

WindowFactory WindowFactory::setName(std::string&& name) {
    this->_name = name;
    return *this;
}

WindowFactory WindowFactory::setName(const std::string& name) {
    this->_name = name;
    return *this;
}

WindowFactory WindowFactory::setFullscreen() {
    _flags |= SDL_WINDOW_FULLSCREEN;
    return *this;
}

WindowFactory WindowFactory::setOpenGL() {
    _flags |= SDL_WINDOW_OPENGL;
    return *this;
}

WindowFactory WindowFactory::setOccluded() {
    _flags |= SDL_WINDOW_OCCLUDED;
    return *this;
}

WindowFactory WindowFactory::setHidden() {
    _flags |= SDL_WINDOW_HIDDEN;
    return *this;
}

WindowFactory WindowFactory::setBorderless() {
    _flags |= SDL_WINDOW_BORDERLESS;
    return *this;
}

WindowFactory WindowFactory::setResizable() {
    _flags |= SDL_WINDOW_RESIZABLE;
    return *this;
}

WindowFactory WindowFactory::setMinimized() {
    _flags |= SDL_WINDOW_MINIMIZED;
    return *this;
}

WindowFactory WindowFactory::setMaximized() {
    _flags |= SDL_WINDOW_MAXIMIZED;
    return *this;
}

WindowFactory WindowFactory::setMouseGrabbed() {
    _flags |= SDL_WINDOW_MOUSE_GRABBED;
    return *this;
}

WindowFactory WindowFactory::setInputFocus() {
    _flags |= SDL_WINDOW_INPUT_FOCUS;
    return *this;
}

WindowFactory WindowFactory::setMouseFocus() {
    _flags |= SDL_WINDOW_MOUSE_FOCUS;
    return *this;
}

WindowFactory WindowFactory::setExternal() {
    _flags |= SDL_WINDOW_EXTERNAL;
    return *this;
}

WindowFactory WindowFactory::setModal() {
    _flags |= SDL_WINDOW_MODAL;
    return *this;
}

WindowFactory WindowFactory::setHighPixelDensity() {
    _flags |= SDL_WINDOW_HIGH_PIXEL_DENSITY;
    return *this;
}

WindowFactory WindowFactory::setMouseCapture() {
    _flags |= SDL_WINDOW_MOUSE_CAPTURE;
    return *this;
}

WindowFactory WindowFactory::setMouseRelativeMode() {
    _flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
    return *this;
}

WindowFactory WindowFactory::setAlwaysOnTop() {
    _flags |= SDL_WINDOW_ALWAYS_ON_TOP;
    return *this;
}

WindowFactory WindowFactory::setUtility() {
    _flags |= SDL_WINDOW_UTILITY;
    return *this;
}

WindowFactory WindowFactory::setTooltip() {
    _flags |= SDL_WINDOW_TOOLTIP;
    return *this;
}

WindowFactory WindowFactory::setPopupMenu() {
    _flags |= SDL_WINDOW_POPUP_MENU;
    return *this;
}

WindowFactory WindowFactory::setKeyboardGrabbed() {
    _flags |= SDL_WINDOW_KEYBOARD_GRABBED;
    return *this;
}

WindowFactory WindowFactory::setVulkan() {
    _flags |= SDL_WINDOW_VULKAN;
    return *this;
}

WindowFactory WindowFactory::setMetal() {
    _flags |= SDL_WINDOW_METAL;
    return *this;
}

WindowFactory WindowFactory::setTransparent() {
    _flags |= SDL_WINDOW_TRANSPARENT;
    return *this;
}

WindowFactory WindowFactory::setNotFocusable() {
    _flags |= SDL_WINDOW_NOT_FOCUSABLE;
    return *this;
}
