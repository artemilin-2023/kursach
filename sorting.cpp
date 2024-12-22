#include "stack.h"

using database::core::list::node;

namespace database {
namespace core {
namespace sorting {

template<class T>
void swap(node<T>* left, node<T>* right) {
    auto tmp = left->data;
    left->data = right->data;
    right->data = tmp;
}

template<class T>
void quick_sort(linked_list<T>* list, std::function<int(const T&, const T&)> comparator) {

    ::database::core::stack::stack<std::pair<int, int>> sort_stack = ::database::core::stack::stack<std::pair<int, int>>();
    sort_stack.push(std::pair(0, list->size() - 1));

    while (!sort_stack.empty()) {
        auto [low_i, high_i] = sort_stack.top();
        sort_stack.pop();
        if (low_i >= high_i)
            continue;

        auto pivot = list->nodeAt(low_i)->data;
        int i = low_i - 1, j = high_i + 1;

        while (true) {
            do {
                i++;
            } while (comparator(list->nodeAt(i)->data, pivot) < 0);

            do {
                j--;
            } while (comparator(list->nodeAt(j)->data, pivot) > 0);

            if (i >= j)
                break;

            swap(list->nodeAt(i), list->nodeAt(j));
        }

        sort_stack.push(std::pair(low_i, j));
        sort_stack.push(std::pair(j + 1, high_i));
    }
}
}
    }
}