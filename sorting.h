#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#ifndef KURSACH_SORTING_H
#define KURSACH_SORTING_H

#include <functional>

#include "linked_list.h"


template<class T>
linked_list<T> quick_sort(linked_list<T> list, std::function<bool(const T&, const T&)> comparator);


#endif

#pragma clang diagnostic pop