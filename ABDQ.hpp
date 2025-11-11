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

    ABDQ(ABDQ&& other) noexcept : data_(other.data), capacity_(other.capacity_), size_(other.size_), front_(other.front_), back_(other.back_) {
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        other.size_ = 0;
    }
    ABDQ& operator=(const ABDQ& other) {
        if (this != &other) {
            delete[] data_;
            data_ = new T[other.capacity_];
            capacity_ = other.capacity_;
            size_ = other.size_;
            front_ = other.front_;
            back_ = other.back_;
            for (std::size_t i = 0; i < capacity_; i++) {
                data_[i] = other.data_[i];
            }
        }
        return *this;
    }

    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            capacity_ = other.capacity_;
            size_ = other.size_;
            front_ = other.front_;
            back_ = other.back_;
            other.data_ = nullptr;
            other.capacity_ = 0;
            other.front_ = 0;
            other.back_ = 0;
            other.size_ = 0;
        }
    }
    ~ABDQ() override {
        delete[] data_;
    }

    // Insertion
    void pushFront(const T& item) override {
        if (size_ == capacity_) {
            std::size_t newCapacity = capacity_ * SCALE_FACTOR;
            T* newData = new T[newCapacity];
            for (std::size_t i = 0; i < capacity_; i++) {
                newData[i] = data_[i];
            }
            delete[] data_;
            data_ = newData;
            capacity_ = newCapacity;
            front_ = 0;
            back_ = size_;
        }
        data_[front_] = item;
        size_++;
    }

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
