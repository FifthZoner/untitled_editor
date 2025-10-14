//
// Created by fifthzoner on 14/10/2025.
//

#include "taskManager.hpp"

#include <iostream>

#include "../options.hpp"

using namespace std::chrono_literals;

void TaskManagerFunction(TaskManager* manager) {
    auto& pendingTasks = manager->pendingTasks;
    auto& runners = manager->runners;
    auto& killSwitch = manager->killSwitch;
    auto& stackMutex = manager->stackMutex;
    auto freeRunners = runners.size();

    while (not killSwitch) {

        // managing current tasks
        if (freeRunners != runners.size()) {
            for (auto& n : runners) {
                auto state = n->getState();
                switch (state) {
                case TaskRunner::Free:
                    break;
                case TaskRunner::Processing:
                case TaskRunner::Assigning:
                case TaskRunner::Busy:
                    if (n->isOverTime())
                        n->sendGracefulEnd(2000ms);
                    break;
                case TaskRunner::Stopping:
                    if (n->isOverTime())
                        n->terminateTask();
                    freeRunners++;
                    break;
                case TaskRunner::Done: {
                    auto result = n->join();
                    freeRunners++;
                    if (result.has_value() and not result.value().ok())
                        std::cout << "Task ended with error: " << result.value().message() << "!\n";
                    break;
                }
                }
            }
        }

        if (pendingTasks.empty() or not freeRunners) {
            std::this_thread::sleep_for(1ms);
            continue;
        }

        // getting the task to run
        stackMutex.lock();

        Task&& task = std::move(pendingTasks[pendingTasks.size() - 1]);
        pendingTasks.pop_back();

        stackMutex.unlock();

        // there must be a free runner so we get it and start the task
        for (auto& n : runners)
            if (n->getState() == TaskRunner::Free) {
                n->startTask(std::move(task));
                freeRunners--;
                break;
            }
    }

    // if there are runners running after the switch we need to end them
    if (freeRunners != runners.size()) {
        for (auto& n : runners) {
            auto state = n->getState();
            if (state == TaskRunner::Done) {
                n->join();
                freeRunners++;
            }
            else if (state != TaskRunner::Free and state != TaskRunner::Stopping) {
                n->sendGracefulEnd(2000ms);
            }
        }

        while (freeRunners != runners.size()) {
            std::this_thread::sleep_for(1ms);

            for (auto& n : runners) {
                auto state = n->getState();
                if (state == TaskRunner::Done) {
                    n->join();
                    freeRunners++;
                }
                else if (n->isOverTime()) {
                    n->terminateTask();
                    freeRunners++;
                }
            }
        }
    }
}

TaskManager::TaskManager(const Options& options) {
    runners.resize(options.taskRunnerAmount);
    for (auto& n : runners)
        n = std::make_unique<TaskRunner>();

    thread = std::thread(TaskManagerFunction, this);
}

void TaskManager::RunTask(Task&& task) {
    stackMutex.lock();
    pendingTasks.emplace_back(task);
    stackMutex.unlock();
}

TaskManager::~TaskManager() {
    killSwitch = true;
    thread.join();
}
