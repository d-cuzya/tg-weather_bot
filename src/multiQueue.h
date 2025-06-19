#ifndef MULTIQUEUE_H
#define MULTIQUEUE_H

#include <thread>
#include <chrono>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

class multitQueue {
    std::queue<std::function<void()>> tasks;
    std::mutex tasksMutex;
    std::condition_variable tasksCv;

public:
    void pushTask(std::function<void()> task) {
        {
            std::lock_guard<std::mutex> lock(tasksMutex);
            tasks.push(std::move(task));
        }
        tasksCv.notify_one();
    }

    std::function<void()> popTask() {
        std::unique_lock<std::mutex> lock(tasksMutex);
        tasksCv.wait(lock, [this] { return !tasks.empty(); });
        auto task = std::move(tasks.front());
        tasks.pop();
        return task;
    }

    bool empty() {
        std::lock_guard<std::mutex> lock(tasksMutex);
        return tasks.empty();
    }
};

#endif // MULTIQUEUE_H
