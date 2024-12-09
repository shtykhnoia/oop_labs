#pragma once
#include <memory_resource>
#include <map>
#include <cstddef>
#include <cstdlib>
#include <stdexcept>

class CustomMemoryResource : public std::pmr::memory_resource {
public:
    explicit CustomMemoryResource(std::size_t totalSize)
        : m_totalSize(totalSize), m_offset(0) {
        m_memory = static_cast<char*>(std::malloc(m_totalSize));
        if (!m_memory) {
            throw std::bad_alloc();
        }
    }

    ~CustomMemoryResource() override {
        std::free(m_memory);
    }

protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override {
        for (auto it = m_freeBlocks.begin(); it != m_freeBlocks.end(); ++it) {
            void* ptr = it->first;
            std::size_t blockSize = it->second;

            std::uintptr_t address = reinterpret_cast<std::uintptr_t>(ptr);
            std::size_t adjustment = alignmentAdjustment(address, alignment);
            if (blockSize >= bytes + adjustment) {
                m_allocations[ptr] = bytes;
                m_freeBlocks.erase(it);
                return ptr;
            }
        }

        std::uintptr_t currentAddress = reinterpret_cast<std::uintptr_t>(m_memory + m_offset);
        std::size_t adjustment = alignmentAdjustment(currentAddress, alignment);

        if (m_offset + adjustment + bytes > m_totalSize) {
            throw std::bad_alloc();
        }

        m_offset += adjustment;
        void* ptr = m_memory + m_offset;
        m_allocations[ptr] = bytes;
        m_offset += bytes;

        return ptr;
    }

    void do_deallocate(void* ptr, std::size_t bytes, std::size_t /*alignment*/) override {
        m_allocations.erase(ptr);
        m_freeBlocks[ptr] = bytes;
    }

    bool do_is_equal(const memory_resource& other) const noexcept override {
        return this == &other;
    }

private:
    char* m_memory;
    std::size_t m_totalSize;
    std::size_t m_offset;
    std::map<void*, std::size_t> m_allocations;
    std::map<void*, std::size_t> m_freeBlocks;

    static std::size_t alignmentAdjustment(std::uintptr_t address, std::size_t alignment) {
        std::size_t misalignment = address % alignment;
        return misalignment ? (alignment - misalignment) : 0;
    }
};