#include "startup.hpp"

#include <functional>
#include <iostream>
#include <optional>
#include <unordered_map>
#include <filesystem>

namespace fs = std::filesystem;

void ShowHelpScreen() {
    std::cout << "Options help\n";
    std::cout << "Command syntax: <executable> {options with either - or --}\n";
    std::cout << "Command line options:\n";
    std::cout << "h, help              - displays this help screen\n";
    std::cout << "tasks={amount}       - sets the maximum amount of threads spawned for task execution\n";
    std::cout << "addModuleDir={path}\n";
    std::cout << "addModulePath={path} - adds given path to search for modules\n";
    std::cout << "overrideModulesPath  - sets skips adding default modules path\n";
}

std::optional<Error> HandlerHelp(Options& options, std::string value) {
    ShowHelpScreen();
    return Error(nullptr);
}

std::optional<Error> HandlerTasks(Options& options, std::string value) {
    if (value.empty())
        return Error("Task amount must be specified!");
    for (auto& n : value)
        if (n < '0' or n > '9')
            return Error("Invalid task amount argument format!");
    uint32_t amount = std::stoul(value);
    if (amount <= 0)
        return Error("Task amount must be at least 1!");
    options.taskRunnerAmount = amount;
    return std::nullopt;
}

std::optional<Error> HandlerAddModuleDir(Options& options, std::string value) {
    if (value.empty())
        return Error("Task amount must be specified!");
    if (not fs::exists(value))
        return Error("Path: " + value + " is not valid!");
    if (not fs::is_directory(value))
        return Error("Path: " + value + " is not a directory!");
    options.modulePaths.emplace_back(std::move(value));
    return std::nullopt;
}

std::optional<Error> HandlerOverrideModulesPath(Options& options, std::string value) {
    options.overrideModulesPath = true;
    return std::nullopt;
}

std::unordered_map<std::string, std::function<std::optional<Error>(Options& options, std::string)>> argumentHandlers{
    {"h", HandlerHelp},
    {"help", HandlerHelp},
    {"tasks", HandlerTasks},
    {"addmoduledir", HandlerAddModuleDir},
    {"addmodulepath", HandlerAddModuleDir},
    {"overrideModulesPath", HandlerOverrideModulesPath}
};

std::optional<Error> ResolvePaths(Options& options, const char* pathArg) {
    options.executablePath = pathArg;

    if (not options.overrideModulesPath)
    {
        TrueOrOptional(options.executablePath.contains('/'), "Non unix paths not supported yet!");
        options.modulePaths.push_back(options.executablePath.substr(0, options.executablePath.find_last_of('/')) + "/modules/");
        TrueOrOptional(fs::exists(options.modulePaths.back())
            and fs::is_directory(options.modulePaths.back()), "Invalid main modules path!");
    }

    return std::nullopt;
}

std::expected<Options, Error> LoadOptions(int argc, char** argv) {

    Options options;

    for (
#ifdef TARGET_UNIX
        int n = 1;
#else
#error Argument parsing not implemented on non-unix enviroments
#endif
        n < argc; n++) {
        std::string str = argv[n];
        auto amountOfLines = str.starts_with("--") ? 2
                           : str.starts_with("-") ? 1 : 0;

        // checking the correctness of the argument
        TrueOrUnexpected(amountOfLines != 0 and str.length() >= 1 + amountOfLines, "Invalid argument: " + str);

        // now changing it into an identifier
        std::string flag{};
        std::string value{};

        auto valueStart = str.find_first_of('=');
        if (valueStart != std::string::npos) {
            TrueOrUnexpected(valueStart > amountOfLines, "Argument must be specified before value!");
            flag = str.substr(amountOfLines, valueStart - amountOfLines);
            value = str.substr(valueStart + 1);
        }
        else
            flag = str.substr(amountOfLines);

        for (auto& character : flag)
            character = char(std::tolower(character));

        if (TrueOrWarning(argumentHandlers.contains(flag), "Unknown flag: \"" + flag + "\", skipping...\n")) {
            auto result = argumentHandlers[flag](options, std::move(value));
            if (result.has_value())
                return std::unexpected(result.value());
        }
    }

#ifdef TARGET_LINUX
    {
        auto result = ResolvePaths(options, argv[0]);
        if (result.has_value())
            return std::unexpected(result.value());
    }
#else
#error Argument parsing not implemented on non-unix enviroments
#endif

    return std::move(options);
}