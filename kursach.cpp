// kursach.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "database.h"
#include "student.h"

using database::entities::student;

int main()
{
    auto db = database::database_c<student>("data.db");
    
    /*auto person1 = student("a", "a", "a", "a", "a", "a", "a");
    auto person2 = student("b", "a", "a", "a", "a", "a", "a");
    auto person3 = student("c", "a", "a", "a", "a", "a", "a");
    auto person4 = student("d", "a", "a", "a", "a", "a", "a");
    auto person5 = student("e", "a", "a", "a", "a", "a", "a");
    auto person6 = student("f", "a", "a", "a", "a", "a", "a");

    db.startTransaction();
    
    db.add(person3);
    db.add(person2);
    db.add(person1);
    db.add(person6);
    db.add(person5);
    db.add(person4);

    db.commitTransaction();*/

    auto sorted = db.orderBy([](const student& s1, const student& s2) {
        if (s1.firstName < s2.firstName)
            return -1;
        else if (s1.firstName > s2.firstName)
            return 1;
        return 0;
        });

    auto selected = db.selectBy([](const student& s) {
        return s.firstName == "AA" || s.address == "a";
        });

}
