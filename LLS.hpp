#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS() = default;

    LLS(const LLS& other) : list(other.list) {}

    LLS& operator=(const LLS& rhs) {
        if (this != &rhs) {
            list = rhs.list;
        }
        return *this;
    }

    LLS(LLS&& other) noexcept : list(std::move(other.list)) {}

    LLS& operator=(LLS&& rhs) noexcept {
        if (this != &rhs) {
            list = std::move(rhs.list);
        }
        return *this;
    }

    ~LLS() = default;

    // Insertion
    void push(const T& item) override {
        list.addHead(item);
    }

    // Deletion
    T pop() override {
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

    //Getters
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