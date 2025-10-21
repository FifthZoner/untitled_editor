//
// Created by fifthzoner on 16/10/2025.
//

#ifndef UNTITLED_EDITOR_WINDOW_HPP
#define UNTITLED_EDITOR_WINDOW_HPP


#include <memory>
#include <SDL3/SDL.h>

class Error;
class WindowFactory;

class Window {
    SDL_Window* window = nullptr;
    std::unique_ptr<char> title = nullptr;

    Window() = default;
public:
    Window(const Window& other);
    Window(Window&& other) noexcept ;

    ~Window();

    friend class WindowFactory;
};


#endif //UNTITLED_EDITOR_WINDOW_HPP