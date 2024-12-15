// kursach.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "database.h"
#include "student.h"

using database::entities::student;

int main()
{
    auto db = database::database_c<student>("data.db");

}
