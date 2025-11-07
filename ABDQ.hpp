#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ() : data_(new T[4]), capacity_(4), size_(0), front_(0), back_(0) {}

    explicit ABDQ(std::size_t capacity) : data_(new T[capacity]), capacity_(capacity), size_(0), front_(0), back_(0) {}

    ABDQ(const ABDQ& other) : data(new T[other.capacity_]), capacity_(other.capacity_), size_(other.size_), front_(other.front_), back_(other.back_) {
        for (std::size_t i = 0; i < capacity_; i++) {
            data_[i] = other.data_[i];
        }
    }

    ABDQ(ABDQ&& other) noexcept : data_(other.data)
    ABDQ& operator=(const ABDQ& other);
    ABDQ& operator=(ABDQ&& other) noexcept;
    ~ABDQ() override;

    // Insertion
    void pushFront(const T& item) override;
    void pushBack(const T& item) override;

    // Deletion
    T popFront() override;
    T popBack() override;

    // Access
    const T& front() const override;
    const T& back() const override;

    // Getters
    std::size_t getSize() const noexcept override;

};
