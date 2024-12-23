#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include <exception>
#include <iomanip>

#include "sorting.h"
#include "helpers.h"

using database::core::sorting::quick_sort;

namespace database {
#pragma region database

    const string columnDelimiter = " | ";

    template<class T>
    database<T>::database(string path) {
        this->path = path;
        hasActiveTransaction = false;
        data = readFrom(path);
    }

    template<class T>
    database<T>::~database() {
        data->~linked_list();
    }

    template<class T>
    linked_list<T>* database<T>::readFrom(string path) {
        std::fstream file_input(path);
        
        try {
            if (!file_input.good() || file_input.peek() == EOF)
                return new linked_list<T>{};

            string line;
            auto result = new linked_list<T>{};
            while (std::getline(file_input, line))
            {
                auto entityData = helpers::parse_row(line, columnDelimiter);
                T entity = helpers::map(entityData);
                result->push_back(entity);
            }

            file_input.close();
            return result;
        }
        catch (const std::exception& ex) {
            std::cout << ex.what() << '\n';
            file_input.close();
        }
    }

    template<class T>
    void database<T>::writeTo(string path) {
        std::fstream file_output(path, std::ios::out | std::ios::trunc);
        
        try {
            if (!file_output.good())
                throw std::runtime_error("Can't open the file on the path: " + path);

            for (int i = 0; i < data->size(); i++) {
                auto entityData = helpers::map(data->nodeAt(i)->data);
                for (int j = 0; j < entityData.size(); j++) {
                    file_output << entityData[j];
                    if (j != entityData.size() - 1)
                        file_output << columnDelimiter;
                }
                file_output << '\n';
            }
        }
        catch (const std::exception& ex) {
            file_output.close();
            throw ex;
        }

        file_output.close();
    }

    template<class T>
    void database<T>::rollBack() {
        data = readFrom(path);
    }

    template<class T>
    void database<T>::add(T item) {
        if (!hasActiveTransaction)
            throw std::runtime_error("Start the transaction before adding.");

        data->push_back(item);
    }

    template<class T>
    bool database<T>::deleteBy(int id) {
        if (!hasActiveTransaction)
            throw std::runtime_error("Start the transaction before deleting.");

        if (id < 0 || id >= data->size())
            return false;

        data->erase(id);
        return true;
    }

    template<class T>
    linked_list<T>* database<T>::orderBy(std::function<int(const T&, const T&)> comparator) {
        auto resultList = new linked_list<T>();
        data->copyTo(resultList);

        ::database::core::sorting::quick_sort(resultList, comparator);
        return resultList;
    }

    template<class T>
    linked_list<T>* database<T>::selectBy(std::function<bool(const T&)> selector) {
        auto resultList = new linked_list<T>();
        auto currentNode = data->begin();

        do {
            if (selector(currentNode->data))
                resultList->push_back(currentNode->data);
            currentNode = currentNode->next;
        } while (currentNode != data->begin());

        return resultList;
    }

    template<class T>
    linked_list<T>* database<T>::getAll() {
        return data;
    }

    template<class T>
    void database<T>::startTransaction() {
        if (hasActiveTransaction)
            throw std::runtime_error("Active transaction already exists.");

        hasActiveTransaction = true;
    }

    template<class T>
    bool database<T>::commitTransaction() {
        if (!hasActiveTransaction)
            throw std::runtime_error("Start the transaction before commiting.");

        try
        {
            writeTo(path);
            hasActiveTransaction = false;
            return true;
        }
        catch (const std::exception& ex)
        {
            std::cerr << "commit failed with error: " << ex.what() << '\n';
            std::cout << "rollbacking the transactioin...." << '\n';
            rollBack();
            std::cout << "rallback success." << '\n';
            hasActiveTransaction = false;
            return false;
        }
    }

#pragma endregion
}