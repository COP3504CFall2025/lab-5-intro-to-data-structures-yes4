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

    void ensureCapacity() {
        if (size_ < capacity_) {
            return;
        }

        size_t newCapacity = capacity_ * SCALE_FACTOR;
        T* newData = new T[newCapacity];

        for (std::size_t i = 0; i < size_; ++i) {
            newData[i] = data_[(front_ + i) % capacity_];
        }

        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
        front_ = 0;
        back_ = size_ - 1;
    }

    void shrinkIfNeeded() {
        if (capacity_ <= 4) {
            return;
        }
        if (size_ * 4 >= capacity_) {
            return;
        }

        size_t newCapacity = capacity_ / 2;
        T* newData = new T[newCapacity];

        for (std::size_t i = 0; i < size_; ++i) {
            newData[i] = data_[(front_ + i) % capacity_];
        }

        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
        front_ = 0;
        back_ = size_ - 1;
    }

public:
    // Big 5
    ABDQ() : data_(new T[4]), capacity_(4), size_(0), front_(0), back_(0) {}

    explicit ABDQ(std::size_t capacity) : data_(new T[capacity]), capacity_(capacity), size_(0), front_(0), back_(0) {}

    ABDQ(const ABDQ& other) : data_(new T[other.capacity_]), capacity_(other.capacity_), size_(other.size_), front_(other.front_), back_(other.back_) {
        for (std::size_t i = 0; i < other.capacity_; i++) {
            data_[i] = other.data_[i];
        }
    }

    ABDQ(ABDQ&& other) noexcept : data_(other.data_), capacity_(other.capacity_), size_(other.size_), front_(other.front_), back_(other.back_) {
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
            for (std::size_t i = 0; i < other.capacity_; i++) {
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
        return *this;
    }

    ~ABDQ() override {
        delete[] data_;
    }

    // Insertion
    void pushFront(const T& item) override {
        ensureCapacity();
        if (size_ == 0) {
            data_[front_] = item;
        }
        else {
            front_ = (front_ - 1 + capacity_) % capacity_;
            data_[front_] = item;
        }
        ++size_;
    }

    void pushBack(const T& item) override {
        ensureCapacity();
        if (size_ == 0) {
            data_[back_] = item;
        }
        else {
            back_ = (back_ + 1) % capacity_;
            data_[back_] = item;
        }
        ++size_;
    }

    // Deletion
    T popFront() override {
        if (size_ == 0) {
            throw std::runtime_error("Empty");
        }
        T value = data_[front_];
        if (size_ > 1) {
            front_ = (front_ + 1) % capacity_;
        }
        --size_;
        shrinkIfNeeded();
        return value;
    }

    T popBack() override {
        if (size_ == 0) {
            throw std::runtime_error("Empty");
        }
        T value = data_[back_];
        if (size_ > 1) {
            back_ = (back_ - 1 + capacity_) % capacity_;
        }
        --size_;
        shrinkIfNeeded();
        return value;
    }

    // Access
    const T& front() const override {
        if (size_ == 0) {
            throw std::runtime_error("Empty");
        }
        return data_[front_];
    }

    const T& back() const override {
        if (size_ == 0) {
            throw std::runtime_error("Empty");
        }
        return data_[back_];
    }

    // Getters
    std::size_t getSize() const noexcept override {
        return size_;
    }

    void printForward() {
        printForward();
    }

    void printBackward() {
        printBackward();
    }

};
