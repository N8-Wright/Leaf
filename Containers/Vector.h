#pragma once
#include "Mallocator.h"
#include "Block.h"
#include <cassert>
#include <utility>
namespace Leaf::Containers {
    template<typename T, typename Alloc = Leaf::Allocator::Mallocator>
    class Vector {
    public:
        Vector() {
            m_length = 0;
            m_capacity = 2;
            m_block = m_allocator.Allocate(sizeof(T) * m_capacity);
        }

        ~Vector() {
            std::destroy(static_cast<T*>(m_block.Ptr), static_cast<T*>(m_block.Ptr) + m_length);
            m_allocator.DeallocateAll();
        }

        void Push(const T& value) {
            if (m_length == m_capacity) {
                Grow();
            }

            new(&(static_cast<T*>(m_block.Ptr))[m_length]) T(value);
            m_length++;
        }

        void Push(T&& value) {
            if (m_length == m_capacity) {
                Grow();
            }

            new(&(static_cast<T*>(m_block.Ptr))[m_length]) T(std::move(value));
            m_length++;
        }

        template<typename... Args>
        void Emplace(Args&&... args) {
            if (m_length == m_capacity) {
                Grow();
            }
            new(&(static_cast<T*>(m_block.Ptr))[m_length]) T(std::forward<Args>(args)...);
            m_length++;
        }

        void Insert(const T& value, size_t index) {
            if (index > m_length) {
                return;
            }

            MakeSpaceForInsert(index);
            new(&(static_cast<T*>(m_block.Ptr))[index]) T(value);
        }

        void Insert(T&& value, size_t index) {
            if (index > m_length) {
                return;
            }

            MakeSpaceForInsert(index);
            new(&(static_cast<T*>(m_block.Ptr))[index]) T(std::move(value));
        }

        [[nodiscard]] size_t Length() const noexcept {
            return m_length;
        }

        const T& operator[](size_t index) const noexcept {
            assert(index < m_length);
            return static_cast<T*>(m_block.Ptr)[index];
        }

    private:
        void Grow() {
            m_capacity *= 2;
            auto new_block = m_allocator.Allocate(sizeof(T) * m_capacity);
            std::uninitialized_move_n(static_cast<T*>(m_block.Ptr), m_length, static_cast<T*>(new_block.Ptr));
            std::destroy(static_cast<T*>(m_block.Ptr), static_cast<T*>(m_block.Ptr) + m_length);
            m_allocator.Deallocate(m_block);
            m_block = new_block;
        }

        void MakeSpaceForInsert(size_t index) {
            if (m_length == m_capacity) {
                Grow();
            }

            m_length++;
            auto items = static_cast<T*>(m_block.Ptr);
            for (size_t i = m_length - 1; i > index; i--) {
                new (&items[i]) T(std::move(items[i - 1]));
            }
        }


        size_t m_length;
        size_t m_capacity;
        Allocator::Block m_block;
        Alloc m_allocator;
    };
}