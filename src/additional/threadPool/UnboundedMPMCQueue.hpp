//
// Created by ywx1235144 on 1/17/24.
//
// ywx1235144 is Sergey Yakovlev, FCS student,
// an excellent programmer and just a good person.
// He has written this thread pool

#include <cassert>
#include <condition_variable>
#include <deque>
#include <mutex>
#include <optional>
#include <stdexcept>

/// @author Sergey Yakovlev, FCS student
/// @file UnboundedMPMCQueue.hpp
/// TODO: Description parameters from class UnboundedMPMCQueue

#ifndef PLACER_UNBOUNDEDMPMCQUEUE_H
#  define PLACER_UNBOUNDEDMPMCQUEUE_H

namespace Threading {

/// Allows to add tasks and blocking wait for element appearance
/// for multiple writers (producers) and multiple readers (consumers).
/// User must guarantee no adding in the closed queue,
/// else runtime error exception will be thrown.

/// class UnboundedMPMCQueue
/// A thread-safe unbounded multiple producer multiple consumer (MPMC) queue
/// @tparam T The type of items stored in the queue
/// @param closed Flag indicating whether the queue is closed
/// @param mutex TO DO:
/// @param not_empty_or_closed Condition variable for signaling queue status.
/// A more detailed description
/// [here](https://en.cppreference.com/w/cpp/thread/condition_variable).
/// @param queue TO DO:
template<typename T>
class UnboundedMPMCQueue {
public:
  /// Create open queue, which will be ready to accept items.
  UnboundedMPMCQueue()                                            = default;

  // Not allow copy.
  UnboundedMPMCQueue(const UnboundedMPMCQueue& other)             = delete;

  UnboundedMPMCQueue& operator=(const UnboundedMPMCQueue& other)  = delete;

  // Not allow move (FIXME).
  UnboundedMPMCQueue(UnboundedMPMCQueue&& other)                  = delete;

  // Not allow move-copy.
  UnboundedMPMCQueue& operator=(const UnboundedMPMCQueue&& other) = delete;

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

  void                add(T item) {
    std::unique_lock lock(mtx);
    if (closed) {
      throw std::runtime_error(
          "Trying to add in the closed queue, which is not allowed"
      );
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

  void close() {
    std::unique_lock lock(mtx);
    closed = true;
    not_empty_or_closed.notify_all();
  }

  /// Block current thread until no item will appearance in the queue
  /// or queue will be closed.
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
    assert(queue.size() > 0);
    T item = std::move(queue.front());
    queue.pop_front();

    return std::make_optional<T>(std::move(item));
  }

private:
  bool                    closed {false};
  std::mutex              mtx {};
  std::condition_variable not_empty_or_closed {};
  std::deque<T>           queue;
};

}  // namespace Threading.

#endif  // PLACER_UNBOUNDEDMPMCQUEUE_H