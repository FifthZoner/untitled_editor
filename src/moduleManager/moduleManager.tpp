//
// Created by fifthzoner on 12/10/2025.
//

#ifndef UNTITLED_EDITOR_MODULE_MANAGER_HPP
#define UNTITLED_EDITOR_MODULE_MANAGER_HPP

#include <expected>

#include "../errors/errors.hpp"
#include <functional>
#ifdef TARGET_LINUX
#include <dlfcn.h>
#else
#error Unsupported target for module loading!
#endif

#include "module.hpp"

namespace {
    std::unordered_map<std::string, Module> loadedModules{};
    std::mutex moduleLoadMutex{};
}

template<typename TInterface>
std::expected<const TInterface*, Error> LoadModule(std::string name, uint64_t currentInterfaceVersion) {
#ifdef TARGET_LINUX

    moduleLoadMutex.lock();

    if (loadedModules.contains(name)) {
        moduleLoadMutex.unlock();
        return std::unexpected(Error("Module: \"" + name + "\" has already been loaded!"));
    }

    void* soHandle = dlopen(name.c_str(), RTLD_LAZY);
    if (soHandle == nullptr) {
        moduleLoadMutex.unlock();
        return std::unexpected(Error("Could not open module shared object file!"));
    }

    typedef uint64_t (*VersionFuncPtr)();
    auto versionFunc = reinterpret_cast<VersionFuncPtr>(dlsym(soHandle, "ModuleInterfaceVersion"));
    if (versionFunc == nullptr) {
        dlclose(soHandle);
        moduleLoadMutex.unlock();
        return std::unexpected(Error("Could not find version function in the module shared object!"));
    }

    try {
        auto interfaceVersion = versionFunc();
        if (interfaceVersion != currentInterfaceVersion) {
            dlclose(soHandle);
            moduleLoadMutex.unlock();
            return std::unexpected(Error("Module version mismatch, expected: " + std::to_string(currentInterfaceVersion) + " but got: " + std::to_string(interfaceVersion) + "!"));
        }
    }
    catch (...) {
        dlclose(soHandle);
        moduleLoadMutex.unlock();
        return std::unexpected(Error("Error while calling version function!"));
    }

    TInterface* interface;

    typedef TInterface* (*SetupFuncPtr)();
    auto setupFunc = reinterpret_cast<SetupFuncPtr>(dlsym(soHandle, "ModuleSetup"));
    if (setupFunc == nullptr) {
        dlclose(soHandle);
        moduleLoadMutex.unlock();
        return std::unexpected(Error("Could not find setup function in the module shared object!"));
    }
    try {
        interface = setupFunc();
        if (interface == nullptr) {
            dlclose(soHandle);
            moduleLoadMutex.unlock();
            return std::unexpected(Error("Interface setup function returned a nullptr!"));
        }
        std::optional<Error> error = interface->isValid();
        if (error.has_value()) {
            dlclose(soHandle);
            moduleLoadMutex.unlock();
            return std::unexpected(error.value());
        }
    }
    catch (...) {
        dlclose(soHandle);
        moduleLoadMutex.unlock();
        return std::unexpected(Error("Error while calling version function!"));
    }

    loadedModules.emplace(name, Module(soHandle, interface));

    moduleLoadMutex.unlock();

    return interface;

#else
#error Unsupported target for module loading!
#endif
}

#endif //UNTITLED_EDITOR_MODULE_MANAGER_HPP