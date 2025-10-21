//
// Created by fifthzoner on 19/10/2025.
//

#include "../module.hpp"

#include "compositor.hpp"

namespace {
    CompositorInterface interface{};
}


extern "C" {
    EXPORT_ATTRIBUTE
    uint64_t ModuleInterfaceVersion() {
        return COMPOSITOR_INTERFACE_VERSION;
    }

    EXPORT_ATTRIBUTE
    CompositorInterface* ModuleSetup() {
        interface.setMainLoop(MainLoop);
        return &interface;
    }
}
