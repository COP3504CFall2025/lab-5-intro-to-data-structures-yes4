#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ() = default;

    LLQ(const LLQ& other) : list(other.list) {}

    LLQ& operator=(const LLQ& other) {
        if (this != &other) {
            list = other.list;
        }
        return *this;
    }

    LLQ(LLQ&& other) noexcept : list(std::move(other.list)) {}

    LLQ& operator=(LLQ&& other) noexcept {
        if (this != &other) {
            list.clear();
            list = std::move(other.list);
        }
        return *this;
    }

    ~LLQ() = default;

    // Insertion
    void enqueue(const T& item) override {
        list.addTail(item);
    }

    // Deletion
    T dequeue() override {
        if (list.getCount() == 0) {
            throw std::runtime_error("is empty");
        }
        T val = list.getHead()->data;
        list.removeHead();
        return val;
    }

    // Access
    T peek() const override {
        if (list.getCount() == 0) {
            throw std::runtime_error("is empty");
        }
        return list.getHead()->data;
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }

    void printForward() {
        list.printForward();
    }

    void printReverse() {
        list.printReverse();
    }

};