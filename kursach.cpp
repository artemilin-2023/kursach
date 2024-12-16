// kursach.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "database.h"
#include "student.h"

using database::entities::student;

int main()
{
    auto db = database::database_c<student>("data.db");

    auto sorted = db.orderBy([](const student& s1, const student& s2) {
        if (&s1 == nullptr || &s2 == nullptr)
            return false;
        return s1.firstName > s2.firstName;
        });

}
