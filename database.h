#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#ifndef KURSACH_DATABASE_H
#define KURSACH_DATABASE_H

#include <string>

#include "linked_list.h"

using std::string;
using database::core::list::linked_list;

namespace database {

    template<class T>
    class database {
    private:
        // properties
        bool hasActiveTransaction;
        string path;
        linked_list<T> data;

        // methods
        void rollBack();
        linked_list<T> readFrom(string path);
        void writeTo(string path);
    public:
        // constructors
        database(string path);
        ~database();

        // methods
        void add(T item);
        bool deleteBy(int id);
        void print(std::vector<std::string> headers, string divider, int width = 20);
        linked_list<T> orderBy(std::function<bool(const T&, const T&)> comparer);
        linked_list<T> selectBy(string query);
        void startTransaction();
        bool commitTransaction();
    };

}

#endif

#pragma clang diagnostic pop