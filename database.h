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
    class database {
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
        database(string path);
        ~database();

        // methods
        void add(T item);
        bool deleteBy(int id);
        linked_list<T>* orderBy(std::function<int(const T&, const T&)> comparator);
        linked_list<T>* selectBy(std::function<bool(const T&)> selector);
        linked_list<T>* getAll();
        void startTransaction();
        bool commitTransaction();
    };

}

#include "database.cpp"
#endif

#pragma clang diagnostic pop