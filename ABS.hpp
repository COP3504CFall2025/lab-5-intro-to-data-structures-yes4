#pragma once

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS() : capacity_(1), curr_size_(0), array_(new T[1]) {
    }

    explicit ABS(const size_t capacity) : capacity_(capacity), curr_size_(0), array_(new T[capacity]) {
    }

    ABS(const ABS &other) : array_(new T[other.capacity_]), capacity_(other.capacity_), curr_size_(other.curr_size_) {
        for (size_t i = 0; i < curr_size_; i++) {
            array_[i] = other.array_[i];
        }
    }


    ABS &operator=(const ABS &rhs) {
        if (this != &rhs) {
            delete[] array_;
            capacity_ = rhs.capacity_;
            curr_size_ = rhs.curr_size_;
            array_ = new T[capacity_];
            for (size_t i = 0; i < curr_size_; i++) {
                array_[i] = rhs.array_[i];
            }
        }
        return *this;
    }

    ABS(ABS &&other) noexcept : capacity_(other.capacity_), curr_size_(other.curr_size_), array_(other.array_) {
        other.array_ = nullptr;
        other.capacity_ = 0;
        other.curr_size_ = 0;
    }

    ABS &operator=(ABS &&rhs) noexcept {
        if (this != &rhs) {
            delete[] array_;
            capacity_ = rhs.capacity_;
            curr_size_ = rhs.curr_size_;
            array_ = rhs.array_;
            rhs.capacity_ = 0;
            rhs.curr_size_ = 0;
            rhs.array_ = nullptr;
        }
        return *this;
    }

    ~ABS() noexcept override {
        delete[] array_;
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override {return curr_size_;}

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept {return capacity_;}

    // Return underlying data for the stack
    [[nodiscard]] T *getData() const noexcept {return array_;}

    // Push item onto the stack
    void push(const T &data) override {
        if (curr_size_ == capacity_) {
            std::size_t new_capacity = capacity_ * scale_factor_;
            T* temp_array_ = new T[new_capacity];
            for (size_t i = 0; i < curr_size_; i++) {
                temp_array_[i] = array_[i];
            }
            delete[] array_;
            array_ = temp_array_;
            capacity_ = new_capacity;
        }
        array_[curr_size_] = data;
        curr_size_++;
    }

    T peek() const override {
        if (curr_size_ == 0) {
            throw std::runtime_error("is empty");
        }
        return array_[curr_size_ - 1];
    }

    T pop() override {
        if (curr_size_ == 0) {
            throw std::runtime_error("is empty");
        }
        --curr_size_;
        T val = array_[curr_size_];

        if ((capacity_ >= 4 && curr_size_ > 0 && curr_size_ * 4 <= capacity_) || (capacity_ == 2 && curr_size_ <= 1)) {
            size_t new_capacity = capacity_ / 2;
            if (new_capacity < 1) new_capacity = 1;
            T* new_array = new T[new_capacity];
            for (size_t i = 0; i < curr_size_; i++) {
                new_array[i] = array_[i];
            }
            delete[] array_;
            array_ = new_array;
            capacity_ = new_capacity;
        }
        return val;
    }

    void printForward() {
        for (size_t i = 0; i < curr_size_; i++) {
            std::cout << array_[i];
        }
        std::cout << std::endl;
    }

    void printReverse() {
        for (size_t i = curr_size_; i > 0; --i) {
            std::cout << array_[i-1];
        }
        std::cout << std::endl;
    }

private:
    size_t capacity_;
    size_t curr_size_;
    T *array_;
    static constexpr size_t scale_factor_ = 2;
};
