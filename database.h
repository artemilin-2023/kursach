#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#ifndef KURSACH_DATABASE_H
#define KURSACH_DATABASE_H

#include <string>
#include <functional>

#include "linked_list.h"

using std::string;
using database::core::list::linked_list;

namespace database {

    template<class T>
    class database_c {
    private:
        // properties
        bool hasActiveTransaction;
        string path;
        linked_list<T>* data;

        // methods
        void rollBack();
        linked_list<T>* readFrom(string path);
        void writeTo(string path);
    public:
        // constructors
        database_c(string path);
        ~database_c();

        // methods
        void add(T item);
        bool deleteBy(int id);
        void print(std::vector<std::string> headers, string divider, int width = 20);
        linked_list<T>* orderBy(std::function<int(const T&, const T&)> comparator);
        linked_list<T>* selectBy(std::function<bool(const T&)> selector);
        void startTransaction();
        bool commitTransaction();
    };

}

#include "database.cpp"
#endif

#pragma clang diagnostic pop