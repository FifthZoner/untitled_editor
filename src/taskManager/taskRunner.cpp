//
// Created by fifthzoner on 14/10/2025.
//

#include "taskRunner.hpp"

void TaskRunnerFunction(TaskRunner* runner) {
    auto& state = runner->state;
    auto& task = runner->task;
    auto& result = runner->result;
    auto& mutex = runner->mutex;

    mutex.lock();
    state = TaskRunner::Processing;
    mutex.unlock();

    auto err = task.processingFunction(task.inputPtr, task.changesPtr, task.killSwitch);
    if (err.has_value() or task.killSwitch) {
        mutex.lock();
        result = err.value();
        state = TaskRunner::Done;
        mutex.unlock();
        return;
    }

    err = task.assignmentFunction(task.changesPtr, task.targetPtr, task.killSwitch);
    if (err.has_value()) {
        mutex.lock();
        result = err.value();
        state = TaskRunner::Done;
        mutex.unlock();
        return;
    }

    mutex.lock();
    state = TaskRunner::Done;
    mutex.unlock();
}

void TaskRunner::startTask(Task&& taskToRun) {
    task.startTime = chrono::system_clock::now();
    state = Busy;
    thread = std::thread(TaskRunnerFunction, this);
}

void TaskRunner::sendGracefulEnd(chrono::milliseconds timeout) {
    task.startTime = chrono::system_clock::now();
    task.killSwitch = true;
}

void TaskRunner::terminateTask() {
    mutex.lock();
    Warning("Threads should be forcefully terminated in other ways, the program will probably crash");
    thread.detach();
    task.~Task();
    state = Free;
    result = Error(nullptr);
    mutex.unlock();
}

TaskRunner::State TaskRunner::getState() const {
    return state;
}

bool TaskRunner::isOverTime() {
    return task.startTime + task.timeout > chrono::system_clock::now();
}

std::optional<Error> TaskRunner::join() {
    thread.join();
    task.~Task();
    state = Free;
    return std::move(result);
}