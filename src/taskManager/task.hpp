//
// Created by fifthzoner on 13/10/2025.
//

#ifndef UNTITLED_EDITOR_TASK_HPP
#define UNTITLED_EDITOR_TASK_HPP

#include <functional>
#include <chrono>
#include <utility>

#include "../errors/errors.hpp"

namespace chrono = std::chrono;

class TaskRunner;

/// \brief Stores data about a specific task to complete
class Task {
    std::function<std::optional<Error>(const void*, void*, const bool&)> processingFunction = nullptr;
    std::function<std::optional<Error>(const void*, void*, const bool&)> assignmentFunction = nullptr;
    std::function<void()> inputDestructor = nullptr;
    std::function<void()> changesDestructor = nullptr;
    chrono::system_clock::time_point startTime{};
    chrono::milliseconds timeout{};
    void* inputPtr = nullptr;
    void* changesPtr = nullptr;
    void* targetPtr = nullptr;
    bool killSwitch = false;
#ifdef BUILD_DEBUG
    std::string taskName{};
#endif

public:

    Task() = default;

    /// \brief Creates a new task, the only constructor for this type
    /// the bool in function is the abort signal, expected behaviour is to return an ok error when it's true
    /// if it's ignored for too long the task will be terminated the hard way
    /// \tparam TInput type of input variable
    /// \tparam TChanges type of changes storage variable
    /// \tparam TTarget type of target to apply changes to
    /// \param input input variable r-value
    /// \param target application target reference
    /// \param processingFunction function that does the calculating
    /// \param assignmentFunction function that applies the changes
    /// \param timeout time after which to consider the task stuck
    template <typename TInput, typename TChanges, typename TTarget>
    Task(TInput&& input, TTarget& target,
        std::function<std::optional<Error>(const TInput&, TChanges&, const bool&)> processingFunction,
        std::function<std::optional<Error>(const TChanges&, TTarget&, const bool&)> assignmentFunction,
        const chrono::milliseconds timeout) {

            {
                TInput* ptr = static_cast<TInput*>(std::malloc(sizeof(TInput)));
                *ptr = input;
                inputDestructor = [=] { ptr->~TInput(); };
                inputPtr = ptr;
            }

            {
                TChanges* ptr = static_cast<TChanges*>(std::malloc(sizeof(TChanges)));
                *ptr = {};
                changesDestructor = [=] { ptr->~TChanges(); };
                changesPtr = ptr;
            }

            targetPtr = &target;
            this->timeout = timeout;

            this->processingFunction = [processingFunction](auto i, auto c, auto b) {
                return processingFunction(*static_cast<const TInput*>(i), *static_cast<TChanges*>(c), b);
            };
            this->assignmentFunction = [assignmentFunction](auto c, auto t, auto b) {
                return assignmentFunction(*static_cast<const TChanges*>(c), *static_cast<TTarget*>(t), b);
            };
    }

    /// \brief This one additionally assigns the task name, for usage refer to main constructor,
    /// should never be called in release, for that use DebugArg(arg), but it won't break the program
    /// \tparam TInput type of input variable
    /// \tparam TChanges type of changes storage variable
    /// \tparam TTarget type of target to apply changes to
    /// \param input input variable r-value
    /// \param target application target reference
    /// \param processingFunction function that does the calculating
    /// \param assignmentFunction function that applies the changes
    /// \param timeout time after which to consider the task stuck
    /// \param taskName name of the task, only in debug, use the DebugArg(arg) macro
    template <typename TInput, typename TChanges, typename TTarget>
    Task(TInput&& input, TTarget& target,
        std::function<std::optional<Error>(const TInput&, TChanges&, const bool&)> processingFunction,
        std::function<std::optional<Error>(const TChanges&, TTarget&, const bool&)> assignmentFunction,
        const chrono::milliseconds timeout, std::string taskName) :
    Task(input, target, processingFunction, assignmentFunction, timeout) {
#ifdef BUILD_DEBUG
        this->taskName = std::move(taskName);
#endif
    }

    explicit Task(const Task& other);
    Task(Task&& other) noexcept;

    ~Task();

    friend class TaskRunner;
    friend void TaskRunnerFunction(TaskRunner* runner);
};

#endif //UNTITLED_EDITOR_TASK_HPP