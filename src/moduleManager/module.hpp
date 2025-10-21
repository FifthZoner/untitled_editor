//
// Created by fifthzoner on 19/10/2025.
//

#ifndef UNTITLED_EDITOR_MODULE_HPP
#define UNTITLED_EDITOR_MODULE_HPP
#include <cstdint>
#include <expected>
#include <string>


class Error;

class Module {
    void* handle = nullptr;
    void* interface = nullptr;

public:
    Module(Module&& module) noexcept;
    Module(void* handle, void* interface);

    ~Module();

    template<typename TInterface>
    friend std::expected<TInterface, Error> LoadModule(std::string name, uint64_t currentInterfaceVersion);
};


#endif //UNTITLED_EDITOR_MODULE_HPP