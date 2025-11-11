#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ() = default;

    LLDQ(LLDQ const& other) : list(other.list) {}

    LLDQ& operator=(LLDQ const& other) {
        if (this != &other) {
            list = other.list;
        }
        return *this;
    }

    LLDQ(LLDQ&& other) noexcept : list(std::move(other.list)) {}

    LLDQ& operator=(LLDQ&& other) noexcept {
        if (this != &other) {
            list = std::move(other.list);
        }
        return *this;
    }

    ~LLDQ() = default;

    // Core Insertion Operations
    void pushFront(const T& item) override {
        list.addHead(item);
    }

    void pushBack(const T& item) override {
        list.addTail(item);
    }

    // Core Removal Operations
    T popFront() override {
        if (list.getCount() == 0) {
            throw std::out_of_range("is empty");
        }
        T val = list.getHead()->data;
        list.removeHead();
        return val;
    }

    T popBack() override {
        if (list.getCount() == 0) {
            throw std::out_of_range("is empty");
        }
        T val = list.getTail()->data;
        list.removeTail();
        return val;
    }

    // Element Accessors
    const T& front() const override {
        if (list.getCount() == 0) {
            throw std::out_of_range("is empty");
        }
        return list.getHead()->data;
    }
    const T& back() const override {
        if (list.getCount() == 0) {
            throw std::out_of_range("is empty");
        }
        return list.getTail()->data;
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






