//
// Created by ywx1235144 on 1/17/24.
//
// ywx1235144 is Sergey Yakovlev, FCS student,
// an excellent programmer and just a good person.
// He has written this thread pool 

#include "ThreadPool.h"

using namespace Threading;

void ThreadPool::submit(ThreadPool::Task task) {
    { // Add not processed.
        std::unique_lock lock(mtx);
        ++notProcessed;
    }
    // Add to queue.
    queue.add(std::move(task));
}

void ThreadPool::wait() {
    std::unique_lock lock(mtx);
    // Wait for all tasks will be processed.
    while (notProcessed > 0) {
        processedAll.wait(lock);
    }

    // Now there is no pending tasks.
}

void ThreadPool::work() {
    while (true) {
        auto taskOpt = queue.take(); // block here while there are no tasks or queue not closed.
        if (taskOpt.has_value()) {
            // execute task.
            taskOpt.value()();

            // Mark task as processed.
            {
                std::unique_lock lock(mtx);
                assert(notProcessed > 0);
                --notProcessed;
                if (notProcessed == 0) {
                    processedAll.notify_one();
                }
            }
        } else { // queue closed.
            break;
        }
    }
}

void ThreadPool::spawnWorker() {
    workers.emplace_back([this]() {
        work();
    });
}

ThreadPool::ThreadPool(size_t useThreads) {
    for (size_t worker = 0; worker < useThreads; ++worker) {
        spawnWorker();
    }
}

void ThreadPool::stop() {
    // Close queue.
    queue.close();

    // Wait for workers are done.
    for (auto&& worker : workers) {
        worker.join();
    }

    // Clear the array.
    workers.clear();
    workers.shrink_to_fit();

    // Now thread pool is stopped.
}

ThreadPool::~ThreadPool() {
    stop();
}
