//
// Created by fifthzoner on 16/10/2025.
//

#include "window.hpp"

Window::Window(const Window& other) {
    throw std::exception();
}

Window::Window(Window&& other)  noexcept {
    this->window = other.window;
    this->title = std::move(other.title);
    other.window = nullptr;
}

Window::~Window() {
    if (window != nullptr)
        SDL_DestroyWindow(window);
}
