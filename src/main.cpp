#include <iostream>

#include "generated/version.hpp"
#include "startup/startup.hpp"
#include "taskManager/taskManager.hpp"

int main(const int argc, char** argv) {
    std::cout << "<untitled editor> by Szymon Jabłoński\n";
    std::cout << "Version: "
    << version
    << ", build: "
    << totalBuild
    << " (branch: "
    << branch
    << ", sub-build: "
    << branchBuild
    << "), on: "
    << buildTime
#ifdef BUILD_DEBUG
    << ", debug\n";
#else
    << ", release\n";
#endif

    // preparing startup stuff quickly before loading the ui
    auto result = LoadOptions(argc, argv);
    if (not result) {
        if (result.error().ok()) {
            std::cout << "Execution ended gracefully by an option.\n";
            return 0;
        }
        // TODO: some sort of graphical error message later just so that one might know that this failed
        std::cout << "Critical error: " + result.error().message() << "\nProgram aborted!\n";
        return -1;
    }
    auto options = std::move(result.value());

    auto tasks = TaskManager(options);

    // running stuff here

    std::cout << "Execution finished successfully!\n";
    return 0;
}
