#pragma once

#include <memory>
#include <stdexcept>
#include <iostream>

template <class T>
class Array {
private:
    std::size_t _size;
    std::size_t _capacity;
    std::shared_ptr<T[]> _figures;

    void resize();

public:
    Array();
    ~Array() = default;

    T& operator[](std::size_t index);
    operator double() const;
    
    void push_back(const T& figure);
    void erase(std::size_t index);
    std::size_t size() const;

    T& begin();
    T& end();
    
    void print(std::ostream& os) const;
};

template <class T>
Array<T>::Array() : _size(0), _capacity(1), _figures(std::make_shared<T[]>(_capacity)) {}

template <class T>
T& Array<T>::operator[](std::size_t index) {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    return _figures[index];
}

template <class T>
Array<T>::operator double() const {
    double sum = 0;
    for (std::size_t i = 0; i < _size; ++i) {
        sum += static_cast<double>(*_figures[i]);
    }
    return sum;
}

template <class T>
void Array<T>::print(std::ostream& os) const {
    for (std::size_t i = 0; i < _size; ++i) {
        os << "Figure " << i << ":" << std::endl;
        os << *_figures[i];
        os << "Geometric center: " << _figures[i]->center() << std::endl;
        os << "Area: " << static_cast<double>(*_figures[i]) << std::endl
           << std::endl;
    }
}

template <class T>
void Array<T>::push_back(const T& figure) {
    if (_size >= _capacity) {
        resize();
    }
    _figures[_size] = figure;
    ++_size;
}

template <class T>
void Array<T>::erase(std::size_t index) {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    for (std::size_t i = index; i < _size - 1; ++i) {
        _figures[i] = std::move(_figures[i + 1]);
    }
    --_size;
}

template <class T>
std::size_t Array<T>::size() const {
    return _size;
}

template <class T>
T& Array<T>::begin() {
    if (_size == 0) {
        throw std::out_of_range("Array is empty");
    }
    return _figures[0];
}

template <class T>
T& Array<T>::end() {
    if (_size == 0) {
        throw std::out_of_range("Array is empty");
    }
    return _figures[_size - 1];
}

template <class T>
void Array<T>::resize() {
    _capacity = (_capacity == 0) ? 1 : _capacity * 2;
    auto new_figures = std::make_shared<T[]>(_capacity);
    for (std::size_t i = 0; i < _size; ++i) {
        new_figures[i] = std::move(_figures[i]);
    }
    _figures = new_figures;
}

template <class T>
inline std::ostream &operator<<(std::ostream &os, const Array<T> &figVec)
{
    figVec.print(os);
    return os;
}