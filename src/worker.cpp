#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <chrono>

class BoostWorkerThread {
public:
    BoostWorkerThread()
        : workGuard(boost::asio::make_work_guard(ioContext)),
        workerThread([this]() { ioContext.run(); }) {}

    ~BoostWorkerThread() {
        stop();
    }

    void push(std::function<void()> task) {
        boost::asio::post(ioContext, std::move(task));
    }

    void stop() {
        workGuard.reset();
        ioContext.stop();
        if (workerThread.joinable())
            workerThread.join();
    }

private:
    boost::asio::io_context ioContext;
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type> workGuard;
    std::thread workerThread;
};
