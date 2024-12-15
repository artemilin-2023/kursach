#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#ifndef KURSACH_LINKED_LIST_H
#define KURSACH_LINKED_LIST_H

#include <optional>
#include <iostream>
#include "database.h"

namespace database {
    namespace core {
        namespace list {

            template<class T>
            class node {
            public:
                T data;
                node* next;
                node* prev;

                explicit node(T newData);

                node(T newData, node* newNext, node* newPrev);

                ~node() = default;
            };

            template<class T>
            class linked_list {
            private:
                node<T>* head;
                node<T>* tail;
                int _size;
            public:
                linked_list();

                ~linked_list();

                // node accessors
                node<T>* begin() const; // O(1)
                node<T>* end() const; // O(1)
                node<T>* nodeAt(int index) const; // O(n)
                //capacity
                bool empty() const; // O(1)
                int size() const; // O(1)
                //modifiers
                void clear(); // O(n)
                void insert(node<T>* node, T data); // before node O(n)
                void insert(int pos, T data); // before pos O(n)
                void erase(node<T>* node); // O(1)
                void erase(int index); // O(n)
                void push_back(T data); // O(1)
                void pop_back(); //O(1)
                void push_front(T data); // O(1)
                void pop_front(); // O(1)
                void copyTo(linked_list<T>* anotherList);
            };

        }
    }
}
#endif

#pragma clang diagnostic pop
