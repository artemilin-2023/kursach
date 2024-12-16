#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#ifndef KURSACH_SORTING_H
#define KURSACH_SORTING_H

#include <functional>

#include "linked_list.h"

using database::core::list::linked_list;

namespace database {
    namespace core {
        namespace sorting {
            template<class T>
            void quick_sort(linked_list<T>* list, std::function<int(const T&, const T&)> comparator);
        }
    }
}

#include "sorting.cpp"
#endif

#pragma clang diagnostic pop