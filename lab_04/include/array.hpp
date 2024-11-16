#pragma once

#include <memory>
#include <stdexcept>
#include <iostream>

template <typename T>
class Array {
private:
    std::size_t _size;                              
    std::size_t _capacity;                          
    std::shared_ptr<T[]> _figures;                 

    void resize() {
        _capacity = _capacity == 0 ? 1 : _capacity * 2;
        std::shared_ptr<T[]> new_figures(new T[_capacity]);

        for (std::size_t i = 0; i < _size; ++i) {
            new_figures[i] = std::move(_figures[i]);
        }
        _figures = std::move(new_figures);
    }

public:
    Array() : _size(0), _capacity(1) {
        _figures = std::shared_ptr<T[]>(new T[_capacity]);
    }

    ~Array() = default;

    T& operator[](std::size_t index) {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return _figures[index];
    }

    const T& operator[](std::size_t index) const {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return _figures[index];
    }

    operator double() const {
        double sum = 0.0;
        for (std::size_t i = 0; i < _size; ++i) {
            sum += static_cast<double>(*_figures[i]);
        }
        return sum;
    }

    void print(std::ostream& os) const {
        for (std::size_t i = 0; i < _size; ++i) {
            os << "Figure " << i << ":\n";
            os << *_figures[i];
            os << "Geometric center: " << _figures[i]->center() << "\n";
            os << "Area: " << static_cast<double>(*_figures[i]) << "\n\n";
        }
    }

    void push_back(const T& figure) {
        if (_size >= _capacity) {
            resize();
        }
        _figures[_size] = figure;
        ++_size;
    }

    void erase(std::size_t index) {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        for (std::size_t i = index; i < _size - 1; ++i) {
            _figures[i] = std::move(_figures[i + 1]);
        }
        --_size;
    }

    std::size_t size() const {
        return _size;
    }

    T& begin() {
        if (_size == 0) {
            throw std::out_of_range("Array is empty");
        }
        return _figures[0]; // Возвращаем ссылку на T
    }

    T& end() {
        if (_size == 0) {
            throw std::out_of_range("Array is empty");
        }
        return _figures[_size - 1]; // Возвращаем ссылку на T
    }

};

// Перегрузка оператора вывода для класса Array
template <typename T>
std::ostream& operator<<(std::ostream& os, const Array<T>& array) {
    array.print(os);
    return os;
}
