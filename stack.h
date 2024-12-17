#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#ifndef KURSACH_STACK_H
#define KURSACH_STACK_H

#include <optional>
#include <iostream>

namespace database {
    namespace core {
        namespace stack {

            template<class T>
            class node {
            public:
                T data;
                node* next;

                node(T data);

                node(T data, node* next);

                ~node() = default;
            };

            template<class T>
            class stack {
            private:
                node<T>* peek;
                node<T>* tail;
                int _size;
            public:
                stack();

                ~stack();

                // node accessors
                node<T>* begin() const; // O(1)
                node<T>* end() const; // O(1)
                //capacity
                bool empty() const; // O(1)
                int size() const; // O(1)
                //modifiers
                void clear(); // O(n)
                void push(T data); // O(1)
                T top(); // O(1)
                T pop(); // O(1)
            };

        }
    }
}

#include "stack.cpp"
#endif

#pragma clang diagnostic pop