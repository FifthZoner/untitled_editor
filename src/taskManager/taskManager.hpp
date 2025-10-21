//
// Created by fifthzoner on 13/10/2025.
//

#ifndef UNTITLED_EDITOR_TASK_MANAGER_HPP
#define UNTITLED_EDITOR_TASK_MANAGER_HPP

#include <memory>

#include "taskRunner.hpp"

struct Settings;

class TaskManager {
    std::vector<Task> pendingTasks{};
    std::vector<std::unique_ptr<TaskRunner>> runners{};
    std::thread thread{};
    bool killSwitch = false;

    std::mutex stackMutex{};

public:
    explicit TaskManager(const Settings& settings);

    void RunTask(Task&& task);

    ~TaskManager();

    friend void TaskManagerFunction(TaskManager* manager);
};

#endif //UNTITLED_EDITOR_TASK_MANAGER_HPP