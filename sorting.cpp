#include <stack>

#include "sorting.h"

using database::core::list::node;

namespace database {
namespace core {
namespace sorting {

    template<class T>
    linked_list<T> quick_sort(linked_list<T> list, std::function<bool(const T&, const T&)> comparator) {

        std::stack<std::pair<int, int>> sort_stack{};
        sort_stack.emplace(0, list.size() - 1);

        while (!sort_stack.empty()) {
            auto [low_i, high_i] = sort_stack.top();
            sort_stack.pop();
            if (low_i >= high_i)
                continue;

            int pivot = list.nodeAt(low_i)->data;
            int i = low_i - 1, j = high_i + 1;

            while (true) {
                do {
                    i++;
                } while (!comparator(&list.nodeAt(i)->data, &pivot));

                do {
                    j--;
                } while (comparator(&list.nodeAt(j)->data, &pivot));

                if (i >= j)
                    break;

                swap(list.nodeAt(i), list.nodeAt(j));
            }

            sort_stack.emplace(low_i, j);
            sort_stack.emplace(j + 1, high_i);
        }
    }

    template<class T>
    void swap(node<T> left, node<T> right) {
        auto tmp = left.data;
        left.data = right.data;
        right.data = tmp;
    }

}
}
}