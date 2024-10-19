#pragma once
#include "iostream"
#include "vector"
#include "map"

class Eleven {
private:
    size_t capacity = 0;

    void resize(size_t new_capacity);

    unsigned char *digits = nullptr;
    const std::string ALPHABET = "0123456789A";
    const std::map<unsigned char, int> REV_ALPHABET{
        {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}, {'A', 10}
    };

public:
    Eleven();

    Eleven(const std::initializer_list<unsigned char> digit_list);

    Eleven(const std::string &num);

    Eleven(const size_t size);

    Eleven(const Eleven &other);

    Eleven plus(const Eleven &other) const;

    Eleven minus(const Eleven &other) const;

    bool equal(const Eleven &other) const;

    bool not_equal(const Eleven &other) const;

    bool lower_than(const Eleven &other) const;

    bool greater_than(const Eleven &other) const;

    virtual ~Eleven() noexcept;
};
