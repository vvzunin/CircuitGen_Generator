/**
 * @file ThreadPool.hpp
 * @brief Пул потоков для выполнения задач.
 * @details ywx1235144 is Sergey Yakovlev, FCS student,
 * an excellent programmer and just a good person.
 * He has written this thread pool
 * @author Vladimir Zunin <vzunin@hse.ru>
 * @author Fuuulkrum7 <ilka747428@gmail.com>
 * @author Zunin Vladimir <vzunin@hse.ru>
 */

#pragma once

#include <functional>
#include <thread>

#include "UnboundedMPMCQueue.hpp"

namespace Threading {

/// Allows to execute tasks in multithread manner.
/// It is not allowed to use thread pool in multiple threads.
/// Task process-start times are guaranteed and ordered by their add time.
/**
 * @author Vladimir Zunin <vzunin@hse.ru>
 * @author Fuuulkrum7 <ilka747428@gmail.com>
 * @author Zunin Vladimir <vzunin@hse.ru>
 */
class ThreadPool {
public:
  /// Create thread pool with specified number of threads.
  /**
   * @author Vladimir Zunin <vzunin@hse.ru>
   * @author Fuuulkrum7 <ilka747428@gmail.com>
   * @author Zunin Vladimir <vzunin@hse.ru>
   */
  explicit ThreadPool(size_t useThreads);

  // Not allow copy.
  ThreadPool(const ThreadPool &other) = delete;

  /**
   * @author Vladimir Zunin <vzunin@hse.ru>
   * @author Fuuulkrum7 <ilka747428@gmail.com>
   * @author Zunin Vladimir <vzunin@hse.ru>
   */
  ThreadPool &operator=(const ThreadPool &other) = delete;

  // Not movable (FIX ME).
  ThreadPool(ThreadPool &&other) = delete;

  // Not allow move-copy.
  /**
   * @author Vladimir Zunin <vzunin@hse.ru>
   * @author Fuuulkrum7 <ilka747428@gmail.com>
   * @author Zunin Vladimir <vzunin@hse.ru>
   */
  ThreadPool &operator=(ThreadPool &&other) = delete;

  using Task = std::function<void()>;

  /// Schedule task on execution.
  /**
   * @author Vladimir Zunin <vzunin@hse.ru>
   * @author Fuuulkrum7 <ilka747428@gmail.com>
   * @author Zunin Vladimir <vzunin@hse.ru>
   */
  void submit(Task task);

  /// Wait for all spawned for now tasks complete.
  /**
   * @author Vladimir Zunin <vzunin@hse.ru>
   * @author Fuuulkrum7 <ilka747428@gmail.com>
   * @author Zunin Vladimir <vzunin@hse.ru>
   */
  void wait();

  /// Stop workers. Some tasks can be incomplete.
  /// Blocks until every thread won't be stopped and destroyed.
  /// After that, thread pool can not process new tasks.
  /**
   * @author Vladimir Zunin <vzunin@hse.ru>
   * @author Fuuulkrum7 <ilka747428@gmail.com>
   * @author Zunin Vladimir <vzunin@hse.ru>
   */
  void stop();

  /// Custom destructor which are to stop workers.
  ~ThreadPool();

private:
  // All multithreading is here.
  /**
   * @author Vladimir Zunin <vzunin@hse.ru>
   * @author Fuuulkrum7 <ilka747428@gmail.com>
   * @author Zunin Vladimir <vzunin@hse.ru>
   */
  void work();

  /**
   * @author Vladimir Zunin <vzunin@hse.ru>
   * @author Fuuulkrum7 <ilka747428@gmail.com>
   * @author Zunin Vladimir <vzunin@hse.ru>
   */
  void spawnWorker();

  UnboundedMPMCQueue<Task> queue;

  std::vector<std::thread> workers;

  size_t notProcessed{0};
  std::mutex mtx;

  std::condition_variable processedAll;
};

} // namespace Threading