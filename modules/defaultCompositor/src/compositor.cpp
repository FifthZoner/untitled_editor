//
// Created by fifthzoner on 16/10/2025.
//

#include "compositor.hpp"
#include "window.hpp"
#include "windowFactory.hpp"

std::vector<Window> windows{};

std::optional<Error> MainLoop(Settings& settings, TaskManager& tasks) {
    SDL_Init(SDL_INIT_VIDEO);

    Window window = WindowFactory::New().setSize({256, 256}).setName("Window").Create().value();

    bool run = true;
    while (run) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
                run = false;
            }
        }
    }

    SDL_Quit();
    return std::nullopt;
}