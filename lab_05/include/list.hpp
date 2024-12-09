#pragma once
#include <memory_resource>
#include <iterator>
#include <iostream>

template <typename T>
class PmrList {
    struct Node {
        T value;
        Node* next;

        Node(const T& val, Node* nxt)
            : value(val), next(nxt) {}
    };

    using allocator_type = std::pmr::polymorphic_allocator<Node>;

public:
    explicit PmrList(std::pmr::memory_resource* resource = std::pmr::get_default_resource())
        : alloc(resource), head(nullptr), tail(nullptr){}

    ~PmrList() {
        clear();
        
    }

    void push_front(const T& value) {
        Node* newNode = alloc.allocate(1);
        alloc.construct(newNode, value, head);
        head = newNode;
    }
    
    void push_back(const T& value) {
    Node* newNode = alloc.allocate(1);
    std::allocator_traits<allocator_type>::construct(alloc, newNode, value, nullptr);
    if (tail) {
        tail->next = newNode;
        tail = newNode;
    } 
    else {
        head = tail = newNode;
    }
    }

    void insert(std::size_t index, const T& value) {
    if (index == 0) {
        push_front(value);
        return;
    }

    Node* current = head;
    for (std::size_t i = 0; current && i < index - 1; ++i) {
        current = current->next;
    }

    if (!current) {
        throw std::out_of_range("Index out of bounds");
    }

    Node* newNode = alloc.allocate(1);
    std::allocator_traits<allocator_type>::construct(alloc, newNode, value, current->next);
    current->next = newNode;

    if (newNode->next == nullptr){
        tail = newNode;
    }
    }

    void erase(std::size_t index) {
    if (!head) {
        throw std::out_of_range("Index out of bounds");
    }

    if (index == 0) {
        Node* temp = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        std::allocator_traits<allocator_type>::destroy(alloc, temp);
        alloc.deallocate(temp, 1);
        return;
    }

    Node* current = head;
    for (std::size_t i = 0; current->next && i < index - 1; ++i) {
        current = current->next;
    }

    if (!current->next) {
        throw std::out_of_range("Index out of bounds");
    }

    Node* temp = current->next;
    current->next = temp->next;

    if (current->next == nullptr) {
        tail = current;
    }

    std::allocator_traits<allocator_type>::destroy(alloc, temp);
    alloc.deallocate(temp, 1);
    }

    void clear() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            std::allocator_traits<allocator_type>::destroy(alloc, current);
            alloc.deallocate(current, 1);
            current = next;
        }
        head = nullptr;
    }

    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;

        explicit iterator(Node* node) : current(node) {}

        reference operator*() const { return current->value; }
        pointer operator->() const { return &(current->value); }

        iterator& operator++() {
            current = current->next;
            return *this;
        }

        iterator operator++(int) {
            iterator tmp(*this);
            current = current->next;
            return tmp;
        }

        bool operator==(const iterator& other) const {
            return current == other.current;
        }
        bool operator!=(const iterator& other) const {
            return current != other.current;
        }

    private:
        Node* current;
    };

    iterator begin() { return iterator(head); }
    iterator end()   { return iterator(nullptr); }

private:
    Node* head;
    Node* tail;
    allocator_type alloc;
};