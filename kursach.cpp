// kursach.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "database.h"
#include "student.h"
#include "console_table.h"
#include "kursach.h"

using database::entities::student;
using ConsoleTable = samilton::ConsoleTable;

const std::vector<std::string> headers = { "i", "FIRST NAME", "LAST NAME", "PATRONYMIC", "DATE OF BIRTH", "GROUP", "ADDRESS", "EXAM RESULT" };


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

    app::print_table(headers, db.getAll());

    
    app::print_table(headers, sorted);


    auto selected = db.selectBy([](const student& s) {
        return s.firstName == "b" || s.firstName == "a";
        });

    app::print_table(headers, selected);

    system("pause");
}

void app::print_table(std::vector<std::string> headers, database::core::list::linked_list<student>* data) {
    ConsoleTable table(2, 2, samilton::Alignment::centre);
    table.addRow(headers);

    int i = 0;
    for (auto node = data->begin(); node != data->end(); node = node->next, i++) {
        auto student = node->data;
        table.addRow({
            std::to_string(i),
            student.firstName,
            student.lastName,
            student.patronymic,
            student.dateOfBirth,
            student.group,
            student.address,
            student.examResult
            });
    }
    std::cout << table;
}

