//
// Created by ywx1235144 on 1/17/24.
//
// ywx1235144 is Sergey Yakovlev, FCS student,
// an excellent programmer and just a good person.
// He has written this thread pool

#include <cassert>
#include <condition_variable>
#include <dequeue>
#include <mutex>
#include <optional>
#include <stdexcept>

#ifndef PLACER_UNBOUNDEDMPMCQUEUE_H
#  define PLACER_UNBOUNDEDMPMCQUEUE_H

namespace Threading {

/// Allows to add tasks and blocking wait for element appearance
/// for multiple writers (producers) and multiple readers (consumers).
/// User must guarantee no adding in the closed queue,
/// else runtime error exception will be thrown.
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
  std::dequeue<T>         queue;
};

}  // namespace Threading.

#endif  // PLACER_UNBOUNDEDMPMCQUEUE_H