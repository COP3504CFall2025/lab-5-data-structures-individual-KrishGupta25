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

    // Core Insertion Operations
    void pushFront(const T& item) override
    {
        if (list.getCount() == 0) {throw std::runtime_error("list.getCount() = 0");}
        list.AddHead(item);
    }
    void pushBack(const T& item) override
    {
        if (list.getCount() == 0) {throw std::runtime_error("list.getCount() = 0");}
        list.AddTail(item);
    }

    // Core Removal Operations
    T popFront() override
    {
        if (list.getCount() == 0) {throw std::runtime_error("list.getCount() = 0");}
        T frontElement = list.getHead() -> data;
        list.RemoveHead();
        return frontElement;
    }
    T popBack() override
    {
        if (list.getCount() == 0) {throw std::runtime_error("list.getCount() = 0");}
        T backElement = list.getTail() -> data;
        list.RemoveTail();
        return backElement;
    }

    // Element Accessors
    const T& front() const override { return list.getHead() -> data; }
    const T& back() const override { return list.getTail() -> data; }

    // Getter
    std::size_t getSize() const noexcept override { return list.getCount(); }
};






