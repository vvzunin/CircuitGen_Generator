/**
 * @file UnboundedMPMCQueue.hpp
 * @brief Потокобезопасная неограниченная очередь MPMC (multiple producer
 * multiple consumer).
 * @details ywx1235144 is Sergey Yakovlev, FCS student,
 * an excellent programmer and just a good person.
 * He has written this thread pool
 * @author Vladimir Zunin <vzunin@hse.ru>
 * @author Fuuulkrum7 <ilka747428@gmail.com>
 * @author Даниил Ковалёв <dakovalyov@miem.hse.ru>
 * @author Nikita Indyuchenko <nikitosik.200210@gmail.com>
 * @author Zunin Vladimir <vzunin@hse.ru>
 * @author Alexey Goulyev <avgulev_1@edu.hse.ru>
 */
#include <cassert>
#include <condition_variable>
#include <deque>
#include <mutex>
#include <optional>
#include <stdexcept>

#ifndef PLACER_UNBOUNDEDMPMCQUEUE_H
#define PLACER_UNBOUNDEDMPMCQUEUE_H

namespace Threading {

/// Allows to add tasks and blocking wait for element appearance
/// for multiple writers (producers) and multiple readers (consumers).
/// User must guarantee no adding in the closed queue,
/// else runtime error exception will be thrown.

/// class UnboundedMPMCQueue
/// A thread-safe unbounded multiple producer multiple consumer (MPMC) queue
/// @tparam T The type of items stored in the queue
/// @param closed Flag indicating whether the queue is closed
/// @param mutex Mutex for thread-safe access. @todo Describe in detail.
/// @param not_empty_or_closed Condition variable for signaling queue status.
/// A more detailed description
/// [here](https://en.cppreference.com/w/cpp/thread/condition_variable).
/// @param queue Internal queue (deque) of items. @todo Describe in detail.
/**
 * @author Vladimir Zunin <vzunin@hse.ru>
 * @author Fuuulkrum7 <ilka747428@gmail.com>
 * @author Даниил Ковалёв <dakovalyov@miem.hse.ru>
 * @author Nikita Indyuchenko <nikitosik.200210@gmail.com>
 * @author Zunin Vladimir <vzunin@hse.ru>
 * @author Alexey Goulyev <avgulev_1@edu.hse.ru>
 */
template<typename T>
/**
 * @author Vladimir Zunin <vzunin@hse.ru>
 * @author Fuuulkrum7 <ilka747428@gmail.com>
 * @author Даниил Ковалёв <dakovalyov@miem.hse.ru>
 * @author Nikita Indyuchenko <nikitosik.200210@gmail.com>
 * @author Zunin Vladimir <vzunin@hse.ru>
 * @author Alexey Goulyev <avgulev_1@edu.hse.ru>
 */
class UnboundedMPMCQueue {
public:
  /// Create open queue, which will be ready to accept items.
  /**
   * @author Vladimir Zunin <vzunin@hse.ru>
   * @author Fuuulkrum7 <ilka747428@gmail.com>
   * @author Даниил Ковалёв <dakovalyov@miem.hse.ru>
   * @author Nikita Indyuchenko <nikitosik.200210@gmail.com>
   * @author Zunin Vladimir <vzunin@hse.ru>
   * @author Alexey Goulyev <avgulev_1@edu.hse.ru>
   */
  UnboundedMPMCQueue() = default;

  // Not allow copy.
  /**
   * @author Vladimir Zunin <vzunin@hse.ru>
   * @author Fuuulkrum7 <ilka747428@gmail.com>
   * @author Даниил Ковалёв <dakovalyov@miem.hse.ru>
   * @author Nikita Indyuchenko <nikitosik.200210@gmail.com>
   * @author Zunin Vladimir <vzunin@hse.ru>
   * @author Alexey Goulyev <avgulev_1@edu.hse.ru>
   */
  UnboundedMPMCQueue(const UnboundedMPMCQueue &other) = delete;

  /**
   * @author Vladimir Zunin <vzunin@hse.ru>
   * @author Fuuulkrum7 <ilka747428@gmail.com>
   * @author Даниил Ковалёв <dakovalyov@miem.hse.ru>
   * @author Nikita Indyuchenko <nikitosik.200210@gmail.com>
   * @author Zunin Vladimir <vzunin@hse.ru>
   * @author Alexey Goulyev <avgulev_1@edu.hse.ru>
   */
  UnboundedMPMCQueue &operator=(const UnboundedMPMCQueue &other) = delete;

  // Not allow move (FIXME).
  UnboundedMPMCQueue(UnboundedMPMCQueue &&other) = delete;

  // Not allow move-copy.
  /**
   * @author Vladimir Zunin <vzunin@hse.ru>
   * @author Fuuulkrum7 <ilka747428@gmail.com>
   * @author Даниил Ковалёв <dakovalyov@miem.hse.ru>
   * @author Nikita Indyuchenko <nikitosik.200210@gmail.com>
   * @author Zunin Vladimir <vzunin@hse.ru>
   * @author Alexey Goulyev <avgulev_1@edu.hse.ru>
   */
  UnboundedMPMCQueue &operator=(const UnboundedMPMCQueue &&other) = delete;

  /// Add task.

  /// @brief add designed to add an item to the queue
  /// @param item the item to be added to the queue
  /// @code
  /// // Creating a queue for integers.
  /// Threading::UnboundedMPMCQueue<int> queue;
  /// // Adding items to the queue
  /// queue.add(42);
  /// queue.add(17);
  /// queue.add(99);
  /// @endcode
  /// @throw std::runtime_error. It is thrown out if an attempt is made to
  /// add an item to a closed queue

  /**
   * @author Vladimir Zunin <vzunin@hse.ru>
   * @author Fuuulkrum7 <ilka747428@gmail.com>
   * @author Даниил Ковалёв <dakovalyov@miem.hse.ru>
   * @author Nikita Indyuchenko <nikitosik.200210@gmail.com>
   * @author Zunin Vladimir <vzunin@hse.ru>
   * @author Alexey Goulyev <avgulev_1@edu.hse.ru>
   */
  void add(T item) {
    std::unique_lock lock(mtx);
    if (closed) {
      throw std::runtime_error(
          "Trying to add in the closed queue, which is not allowed");
    }
    queue.emplace_back(std::move(item));
    not_empty_or_closed.notify_one();
  }

  /// Close queue. All waiting threads will receive nullopt.

  /// @brief close it is used to close the queue
  /// Example usage:
  /// @code
  /// // Closing the queue
  /// queue.close()
  /// @endcode

  /**
   * @author Vladimir Zunin <vzunin@hse.ru>
   * @author Fuuulkrum7 <ilka747428@gmail.com>
   * @author Даниил Ковалёв <dakovalyov@miem.hse.ru>
   * @author Nikita Indyuchenko <nikitosik.200210@gmail.com>
   * @author Zunin Vladimir <vzunin@hse.ru>
   * @author Alexey Goulyev <avgulev_1@edu.hse.ru>
   */
  void close() {
    std::unique_lock lock(mtx);
    closed = true;
    not_empty_or_closed.notify_all();
  }

  /// Block current thread until no item will appearance in the queue
  /// or queue will be closed.
  /**
   * @author Vladimir Zunin <vzunin@hse.ru>
   * @author Fuuulkrum7 <ilka747428@gmail.com>
   * @author Даниил Ковалёв <dakovalyov@miem.hse.ru>
   * @author Nikita Indyuchenko <nikitosik.200210@gmail.com>
   * @author Zunin Vladimir <vzunin@hse.ru>
   * @author Alexey Goulyev <avgulev_1@edu.hse.ru>
   */
  std::optional<T> take() {
    std::unique_lock lock(mtx);
    // Wait for queue to become not empty or closed.
    while (queue.empty() && !closed) {
      not_empty_or_closed.wait(lock);
    }
    if (closed) {
      return std::nullopt;
    }

    // Get task.
    /**
     * @author Vladimir Zunin <vzunin@hse.ru>
     * @author Fuuulkrum7 <ilka747428@gmail.com>
     * @author Даниил Ковалёв <dakovalyov@miem.hse.ru>
     * @author Nikita Indyuchenko <nikitosik.200210@gmail.com>
     * @author Zunin Vladimir <vzunin@hse.ru>
     * @author Alexey Goulyev <avgulev_1@edu.hse.ru>
     */
    assert(queue.size() > 0);
    /**
     * @author Vladimir Zunin <vzunin@hse.ru>
     * @author Fuuulkrum7 <ilka747428@gmail.com>
     * @author Даниил Ковалёв <dakovalyov@miem.hse.ru>
     * @author Nikita Indyuchenko <nikitosik.200210@gmail.com>
     * @author Zunin Vladimir <vzunin@hse.ru>
     * @author Alexey Goulyev <avgulev_1@edu.hse.ru>
     */
    T item = std::move(queue.front());
    /**
     * @author Vladimir Zunin <vzunin@hse.ru>
     * @author Fuuulkrum7 <ilka747428@gmail.com>
     * @author Даниил Ковалёв <dakovalyov@miem.hse.ru>
     * @author Nikita Indyuchenko <nikitosik.200210@gmail.com>
     * @author Zunin Vladimir <vzunin@hse.ru>
     * @author Alexey Goulyev <avgulev_1@edu.hse.ru>
     */
    queue.pop_front();

    /**
     * @author Vladimir Zunin <vzunin@hse.ru>
     * @author Fuuulkrum7 <ilka747428@gmail.com>
     * @author Даниил Ковалёв <dakovalyov@miem.hse.ru>
     * @author Nikita Indyuchenko <nikitosik.200210@gmail.com>
     * @author Zunin Vladimir <vzunin@hse.ru>
     * @author Alexey Goulyev <avgulev_1@edu.hse.ru>
     */
    return std::make_optional<T>(std::move(item));
  }

private:
  bool closed{false};
  std::mutex mtx{};
  std::condition_variable not_empty_or_closed{};
  std::deque<T> queue;
};

} // namespace Threading.

#endif // PLACER_UNBOUNDEDMPMCQUEUE_H