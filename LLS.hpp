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

    // Insertion
    void push(const T& item) override
    {
        list.AddHead(item);
    }

    // Deletion
    T pop() override
    {
        if (list.getCount() == 0) {throw std::runtime_error("list.getCount() = 0");}
        T frontElement = list.getHead() -> data;
        list.RemoveHead();
        return frontElement;
    }

    // Access
    T peek() const override 
    {
        if (list.getCount() == 0) {throw std::runtime_error("list.getCount() = 0");} 
        return list.getHead() -> data; 
    }

    //Getters
    std::size_t getSize() const noexcept override { return list.getCount(); }
};