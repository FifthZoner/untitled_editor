//
// Created by fifthzoner on 19/10/2025.
//

#include "module.hpp"

#include <dlfcn.h>
#include <unordered_map>

Module::Module(Module&& module) noexcept {
    this->handle = module.handle;
    this->interface = module.interface;
    module.handle = nullptr;
    module.interface = nullptr;
}

Module::Module(void* handle, void* interface) {
    this->handle = handle;
    this->interface = interface;
}

Module::~Module() {
    if (handle != nullptr) {
        dlclose(handle);
        handle = nullptr;
    }
}