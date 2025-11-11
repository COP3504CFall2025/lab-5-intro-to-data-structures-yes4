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
            newData[i] = data_[i];
        }

        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
        front_ = 0;
        back_ = size_;
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
            newData[i] = data_[i];
        }
        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
        front_ = 0;
        back_ = size_;
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
        data_[front_] = item;
        ++size_;
    }

    void pushBack(const T& item) override {
        ensureCapacity();
        data_[back_] = item;
        ++size_;
    }

    // Deletion
    T popFront() override {
        if (size_ == 0) {
            throw std::out_of_range("Empty");
        }
        T value = data_[front_];
        --size_;
        shrinkIfNeeded();
        return value;
    }

    T popBack() override {
        if (size_ == 0) {
            throw std::out_of_range("Empty");
        }
        T value = data_[back_];
        --size_;
        shrinkIfNeeded();
        return value;
    }

    // Access
    const T& front() const override {
        if (size_ == 0) {
            throw std::out_of_range("Empty");
        }
        return data_[front_];
    }

    const T& back() const override {
        if (size_ == 0) {
            throw std::out_of_range("Empty");
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
