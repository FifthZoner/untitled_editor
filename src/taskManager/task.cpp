//
// Created by fifthzoner on 14/10/2025.
//

#include "task.hpp"

Task::Task(const Task& other) {
    throw std::exception();
}

Task::Task(Task&& other) noexcept {
    this->inputPtr = other.inputPtr;
    this->changesPtr = other.changesPtr;
    this->targetPtr = other.targetPtr;
    this->processingFunction = other.processingFunction;
    this->assignmentFunction = other.assignmentFunction;
    this->timeout = other.timeout;
#ifdef BUILD_DEBUG
    this->taskName = other.taskName;
#endif
}

Task::~Task() {
    if (inputPtr != nullptr) {
        inputDestructor();
        std::free(inputPtr);
    }

    if (changesPtr != nullptr) {
        changesDestructor();
        std::free(changesPtr);
    }

    processingFunction = nullptr;
    assignmentFunction = nullptr;
    inputDestructor = nullptr;
    changesDestructor = nullptr;
    startTime = {};
    timeout = {};
    inputPtr = nullptr;
    changesPtr = nullptr;
    targetPtr = nullptr;
    killSwitch = false;
}