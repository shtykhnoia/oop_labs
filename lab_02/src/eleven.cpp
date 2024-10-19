#include <eleven.h>
#include <stdexcept>
#include <algorithm>

void Eleven::resize(size_t new_capacity) {
    if (new_capacity < capacity)
        throw std::invalid_argument("New capacity is smaller than the old one");

    if (new_capacity == capacity)
        return;

    auto *new_digits = new unsigned char[new_capacity];
    for (size_t i = 0; i < capacity; i++) {
        new_digits[i] = digits[i];
    }

    delete[] digits;
    digits = new_digits;
    capacity = new_capacity;
}

Eleven::Eleven() {
    capacity = 1;
    digits = new unsigned char[1];
    digits[0] = 0;
}

Eleven::Eleven(const std::initializer_list<unsigned char> digit_list) {
    capacity = digit_list.size();
    size_t number_of_nulls = 0;
    auto digits_arr = digit_list.begin();
    for (auto it = digit_list.begin(); it != digit_list.end() - 1; ++it) {
        if (*it != 0) break;
        number_of_nulls++;
    }

    capacity = digit_list.size() - number_of_nulls;
    digits = new unsigned char[capacity];

    for (size_t i = number_of_nulls; i < digit_list.size(); i++) {
        digits[i - number_of_nulls] = digits_arr[i];
    }
}

Eleven::Eleven(const std::string &s) {
    capacity = s.size();
    digits = new unsigned char[capacity];
    for (int i = 0; i < capacity; ++i) {
        digits[i] = s[capacity - 1 - i];
    }
}

Eleven::Eleven(const Eleven &other) {

    capacity = other.capacity;
    digits = new unsigned char[capacity]{};

    for(int i = 0; i < capacity; i++){
        digits[i] = other.digits[i];
    }
    
}

Eleven::Eleven(Eleven&& other) {
    capacity = other.capacity;
    digits = other.digits;
    
    other.digits = nullptr;
    other.capacity = 0;
}

Eleven::Eleven(const size_t size) {
    capacity = size;
    digits = new unsigned char[capacity];
}

Eleven::~Eleven() {
    delete[] digits;
    digits = nullptr;
    capacity = 0;
}

Eleven Eleven::plus(const Eleven &other) const {
    const size_t max_size = std::max(capacity, other.capacity);
    Eleven result;
    result.resize(max_size);
    int sum = 0;

    for (size_t i = 0; i < max_size; i++) {
        sum += i < capacity ? REV_ALPHABET.at(digits[i]) : 0;
        sum += i < other.capacity ? REV_ALPHABET.at(other.digits[i]) : 0;

        result.digits[i] = ALPHABET[sum % 11];
        sum /= 11;
    }

    if (sum) {
        result.resize(max_size + 1);
        result.digits[max_size] = ALPHABET[sum];
    }

    return result;
}
Eleven Eleven::minus(const Eleven &other) const {
    size_t max_size = std::max(capacity, other.capacity);
    Eleven result;
    result.resize(max_size);

    int diff{0};

    for (size_t i = 0; i < max_size; i++) {
        if (i < capacity) { diff += REV_ALPHABET.at(digits[i]); }

        if (i < other.capacity) { diff -= REV_ALPHABET.at(other.digits[i]); }

        if(i >= result.capacity) { result.resize(capacity + 1); }

        if (diff < 0) {
            diff += 11;
            result.digits[i] = ALPHABET[diff];
            diff = -1;
        } else {
            result.digits[i] = ALPHABET[diff];
            diff = 0;
        }
    }
    if (diff != 0) { throw std::out_of_range("Eleven::minus overflow"); }

    return result;
}

bool Eleven::greater_than(const Eleven &other) const {
    size_t max_size = std::max<size_t>(capacity, other.capacity);
    int num1{0}, num2{0};
    for (int i = static_cast<int>(max_size - 1); i >= 0; i--) {
        num1 = i < capacity ? REV_ALPHABET.at(digits[i]) : 0;
        num2 = i < other.capacity ? REV_ALPHABET.at(other.digits[i]) : 0;
        if(num1 != num2) return num1 > num2;
    }
    return false;
}

bool Eleven::lower_than(const Eleven &other) const {
    return other.greater_than(*this);
}

bool Eleven::equal(const Eleven &other) const {
    return !(this->greater_than(other) || this->lower_than(other));
}

bool Eleven::not_equal(const Eleven &other) const {
    return !this->equal(other);
}
