// kursach.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "database.h"
#include "student.h"

using database::entities::student;

int main()
{
    auto db = database::database_c<student>("data.db");

    auto first = student("Artem", "Ilin", "Aleksandrovich", "07.09.2005", "M3O-207b-23", "unknown", "pass");
    auto second = student("AA", "Ilin", "Aleksandrovich", "07.09.2005", "M3O-207b-23", "unknown", "pass");

    db.startTransaction();
    db.add(first);
    db.add(second);
    db.commitTransaction();

}
