#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include <exception>
#include <stdio.h>
#include <iomanip>

#include "database.h"
#include "sorting.h"
#include "helpers.h"


#pragma region database

const string columnDelimiter = " | ";

template<class T>
database_c<T>::database_c(string path) {
    this->path = path;
    hasActiveTransaction = false;
    data = readFrom(path);
}

template<class T>
database_c<T>::~database_c() {
    data.~linked_list();
}

template<class T>
linked_list<T> database_c<T>::readFrom(string path) {
    std::fstream file_input(path);
    if (!file_input.good() || file_input.peek() == EOF)
        return linked_list<T>{};

    string line;
    auto result = linked_list<T>{};
    while (std::getline(file_input, line))
    {
        auto entityData = parse_row(line, columnDelimiter);
        T entity = map(entityData);
        result.push_back(entity);
    }

    return result;
}

template<class T>
void database_c<T>::writeTo(string path) {
    std::fstream file_output(path, std::ios::trunc);
    if (!file_output.good())
        throw std::runtime_error("Can't open the file on the path: " + path);

    for (int i = 0; i < data.size(); i++) {
        auto entityData = map(data.nodeAt(i)->data);
        for (int j = 0; j < entityData.size(); j++) {
            file_output << entityData[j];
            if (j != entityData.size() - 1)
                file_output << columnDelimiter;
        }
        file_output << '\n';
    }
}

template<class T>
void database_c<T>::rollBack() {
    data = readFrom(path);
}

template<class T>
void database_c<T>::add(T item) {
    if (!hasActiveTransaction)
        throw std::runtime_error("Start the transaction before adding.");

    data.push_back(item);
}

template<class T>
bool database_c<T>::deleteBy(int id) {
    if (!hasActiveTransaction)
        throw std::runtime_error("Start the transaction before deleting.");

    if (id < 0 || id >= data.size())
        throw std::invalid_argument("Entity with id " + std::to_string(id) + " don't exist.");

    data.erase(id);
}

template<class T>
void database_c<T>::print(std::vector<std::string> headers, string divider, int width) {
    for (auto header : headers)
        std::cout << divider << std::setw(width) << header;
    std::cout << divider << '\n';

    for (int i = 0; i < data.size(); i++)
        std::cout << divider << i << std::setw(width) << data.nodeAt(i)->data << '\n';
}

template<class T>
linked_list<T> database_c<T>::orderBy(std::function<bool(const T&, const T&)> comparator) {
    auto resultList = linked_list<T>();
    data.copyTo(&resultList);

    quick_sort(resultList, comparator);
    return resultList;
}

#pragma endregion
