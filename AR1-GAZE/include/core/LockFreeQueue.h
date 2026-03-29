#pragma once
#include <atomic>
#include <vector>
#include <cstddef>

template <typename T, size_t Size>
class LockFreeQueue {
private:
    // Aligning to 64 bytes prevents "false sharing" between CPU cache lines, 
    // keeping the sensor thread and rendering thread running at max speed.
    alignas(64) std::atomic<size_t> head_{ 0 };
    alignas(64) std::atomic<size_t> tail_{ 0 };
    std::vector<T> buffer_;

public:
    LockFreeQueue() : buffer_(Size) {}

    // Called by the Sensor thread to drop new data in
    bool push(const T& item) {
        size_t current_tail = tail_.load(std::memory_order_relaxed);
        size_t next_tail = (current_tail + 1) % Size;

        if (next_tail == head_.load(std::memory_order_acquire)) {
            return false; // Queue is full, drop the frame to prevent lag
        }

        buffer_[current_tail] = item;
        tail_.store(next_tail, std::memory_order_release);
        return true;
    }

    // Called by the Graphics/Network thread to read the latest data
    bool pop(T& item) {
        size_t current_head = head_.load(std::memory_order_relaxed);

        if (current_head == tail_.load(std::memory_order_acquire)) {
            return false; // Queue is empty, nothing new to process
        }

        item = buffer_[current_head];
        head_.store((current_head + 1) % Size, std::memory_order_release);
        return true;
    }
};