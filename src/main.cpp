#include <iostream>

#include "../interfaces/compositorInterface.hpp"
#include "generated/version.hpp"
#include "startup/startup.hpp"
#include "taskManager/taskManager.hpp"
#include "../modules/defaultCompositor/src/windowFactory.hpp"
#include "moduleManager/moduleManager.tpp"

using namespace std::chrono_literals;

int main(const int argc, char** argv) {
    std::cout << "<untitled editor> by Szymon Jabłoński\n";
    std::cout << "Version: "
    << version
    << ", build: "
    << totalBuild
    << " (branch: "
    << branch
    << ", branch build: "
    << branchBuild
    << "), on: "
    << buildTime
#ifdef BUILD_DEBUG
    << ", debug\n";
#else
    << ", release\n";
#endif

    // preparing startup stuff quickly before loading the ui
    auto settingsResult = LoadOptions(argc, argv);
    if (not settingsResult) {
        if (settingsResult.error().ok()) {
            std::cout << "Execution ended gracefully by an option.\n";
            return 0;
        }
        // TODO: some sort of graphical error message later just so that one might know that this failed
        std::cout << "Critical error: " + settingsResult.error().message() << "\nProgram aborted!\n";
        return -1;
    }
    auto settings = std::move(settingsResult.value());

    auto tasks = TaskManager(settings);

    // TODO: add settings loading task, etc. here

    auto compositorResult = LoadModule<CompositorInterface>("modules/defaultCompositor/libuntitled_editor_default_compositor.so", 1);
    if (not compositorResult.has_value()) {
        std::cout << "Could not load compositor module with error: \"" << compositorResult.error() << "\"\n";
        return -1;
    }
    const CompositorInterface& compositor = *compositorResult.value();

    auto lastResult = compositor.MainLoop(settings, tasks);
    if (not lastResult.has_value()) {
        std::cout << "Compositor exited with error: \"" << lastResult.error() << "\"\n";
        return -1;
    }
    if (lastResult.value().has_value()) {
        std::cout << "Compositor exited with error: \"" << lastResult.value().value() << "\"\n";
        return -1;
    }

    std::cout << "Execution finished successfully!\n";
    return 0;
}
