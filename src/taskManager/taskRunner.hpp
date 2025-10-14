//
// Created by fifthzoner on 14/10/2025.
//

#ifndef UNTITLED_EDITOR_TASK_RUNNER_HPP
#define UNTITLED_EDITOR_TASK_RUNNER_HPP

#include <thread>

#include "task.hpp"
#include "../errors/errors.hpp"

/// \brief Contains a single node responsible for task execution
class TaskRunner {
public:
    enum State {
        Free, Processing, Assigning, Busy, Stopping, Done
    };

private:
    State state = State::Free;
    std::thread thread{};
    Task task{};
    Error result;
    std::mutex mutex{};

public:
    // management methods

    void startTask(Task&& taskToRun);
    void sendGracefulEnd(chrono::milliseconds timeout);
    void terminateTask();

    // checking methods

    [[nodiscard]] State getState() const;
    [[nodiscard]] bool isOverTime();
    std::optional<Error> join();

    friend void TaskRunnerFunction(TaskRunner* runner);
};

#endif //UNTITLED_EDITOR_TASK_RUNNER_HPP
