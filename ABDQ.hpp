#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)
    T* data_;                 // underlying dynamic array

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ() : capacity_(4), size_(0), front_(0), back_(0), data_(new T[capacity_]) {}

    explicit ABDQ(std::size_t capacity) : 
        capacity_(capacity), size_(0), front_(0), back_(0), data_(new T[capacity_]) {}

    ABDQ(const ABDQ& other) :
        capacity_(other.capacity_), size_(other.size_), front_(0), 
        back_(other.size_), data_(new T[other.capacity_])       
        {
            for (size_t i = 0; i < size_; i++) {
                data_[i] = other.data_[(other.front_ + i) % other.capacity_];
            }
        }

    ABDQ(ABDQ&& other) noexcept :
        capacity_(other.capacity_), size_(other.size_), front_(other.front_), 
        back_(other.back_), data_(other.data_)     
        {
            other.capacity_ = 0;
            other.size_ = 0;
            other.front_ = 0;
            other.back_ = 0;
            other.data_ = nullptr;
        }

    ABDQ& operator=(const ABDQ& other)
    {
        if (this != &other)
        {
            delete[] data_;
            capacity_ = other.capacity_;
            size_ = other.size_;
            front_ = 0;
            back_ = size_;
            data_ = new T[capacity_];

            for (size_t i = 0; i < size_; i++) {
                data_[i] = other.data_[(other.front_ + i) % other.capacity_];
            }
        }
        return *this;
    }

    ABDQ& operator=(ABDQ&& other) noexcept
    {
        if (this != &other)
        {
            delete[] data_;
            capacity_ = other.capacity_;
            size_ = other.size_;
            front_ = other.front_;
            back_ = other.back_;
            data_ = other.data_;

            other.capacity_ = 0;
            other.size_ = 0;
            other.front_ = 0;
            other.back_ = 0;
            other.data_ = nullptr;
        }
        return *this;
    }

    ~ABDQ(){ delete[] data_; }

    void shrinkIfNeeded()
    {
        if (size_ > 0 && (size_ <= capacity_/4) && capacity_ > 4)
        {
            size_t tempCapacity = capacity_/2;
            T* temp = new T[tempCapacity];

            for (size_t i = 0; i < size_; i++) 
            {
                temp[i] = data_[(front_ + i) % capacity_];
            }

            delete[] data_;
            data_ = temp;
            capacity_ = tempCapacity;
            front_ = 0;
            back_ = size_;
        }
    }

    // Insertion
    void pushFront(const T& item) override
    {
        if (size_ == capacity_) {
            T* temp = new T[capacity_ * SCALE_FACTOR];
            for (size_t i = 0; i < size_; i++) {
                temp[i] = data_[(front_ + i) % capacity_];
            }
            delete[] data_;
            data_ = temp;
            capacity_ *= SCALE_FACTOR;
            front_ = 0;
            back_ = size_;
        }

        front_ = (front_ == 0) ? capacity_ - 1 : front_ - 1;
        data_[front_] = item;
        size_++;
    }

    void pushBack(const T& item) override
    {
        if (size_ == capacity_) {
            T* temp = new T[capacity_ * SCALE_FACTOR];
            for (size_t i = 0; i < size_; i++) {
                temp[i] = data_[(front_ + i) % capacity_];
            }
            delete[] data_;
            data_ = temp;
            capacity_ *= SCALE_FACTOR;
            front_ = 0;
            back_ = size_;
        }

        data_[back_] = item;
        back_ = (back_ + 1) % capacity_;
        size_++;
    }

    // Deletion
    T popFront() override
    {
        if (size_ == 0) {throw std::runtime_error("size = 0");}

        T frontIndex = data_[front_];
        front_ = (front_ + 1) % capacity_;
        size_--;
        shrinkIfNeeded();
        return frontIndex;
    }

    T popBack() override
    {
        if (size_ == 0) {throw std::runtime_error("size = 0");}

        size_t lastIndex = (back_ == 0) ? capacity_ - 1 : back_ - 1;
        T backElement = data_[lastIndex];
        back_ = lastIndex;
        size_--;
        shrinkIfNeeded();
        return backElement;
    }

    // Access
    const T& front() const override 
    {
        if (size_ == 0) {throw std::runtime_error("size = 0");} 
        return data_[front_]; 
    }
    const T& back() const override 
    { 
        if (size_ == 0) {throw std::runtime_error("size = 0");}
        size_t lastIndex = (back_ == 0) ? capacity_ - 1 : back_ - 1;
        return data_[lastIndex]; 
    }
    
    // Getters
    std::size_t getSize() const noexcept override { return size_; }

};
