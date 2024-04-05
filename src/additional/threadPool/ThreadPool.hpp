//
// Created by ywx1235144 on 1/17/24.
//
// ywx1235144 is Sergey Yakovlev, FCS student,
// an excellent programmer and just a good person.
// He has written this thread pool

#pragma once

#include <functional>
#include <thread>

#include "UnboundedMPMCQueue.hpp"

namespace Threading {

/// Allows to execute tasks in multithread manner.
/// It is not allowed to use thread pool in multiple threads.
/// It is guaranteed tasks process-start times and ordered as their add time.
class ThreadPool {
public:
  /// Create thread pool with specified number of threads.
  explicit ThreadPool(size_t useThreads);

  // Not allow copy.
  ThreadPool(const ThreadPool& other)            = delete;

  ThreadPool& operator=(const ThreadPool& other) = delete;

  // Not movable (FIX ME).
  ThreadPool(ThreadPool&& other)                 = delete;

  // Not allow move-copy.
  ThreadPool& operator=(ThreadPool&& other)      = delete;

  using Task                                     = std::function<void()>;

  /// Schedule task on execution.
  void submit(Task task);

  /// Wait for all spawned for now tasks complete.
  void wait();

  /// Stop workers. Some tasks can be incomplete.
  /// Blocks until every thread won't be stopped and destroyed.
  /// After that, thread pool can not process new tasks.
  void stop();

  /// Custom destructor which are to stop workers.
  ~ThreadPool();

private:
  // All multithreading is here.
  void                     work();

  void                     spawnWorker();

  UnboundedMPMCQueue<Task> queue;

  std::vector<std::thread> workers;

  size_t                   notProcessed {0};
  std::mutex               mtx;

  std::condition_variable  processedAll;
};

}  // namespace Threading