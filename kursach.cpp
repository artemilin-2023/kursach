// kursach.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <thread>
#include <chrono>
#include "database.h"
#include "student.h"
#include "console_table.h"
#include "kursach.h"

using database::entities::student;
using ConsoleTable = samilton::ConsoleTable;

const std::vector<std::string> headers = { "i", "FIRST NAME", "LAST NAME", "PATRONYMIC", "DATE OF BIRTH", "GROUP", "ADDRESS", "EXAM RESULT" };
const int sleepTime = 600;

int main()
{
    setlocale(LC_ALL, "");
    std::cout << "КУРСАВАЯ РАБОТА ПО ПРОГРАММИРОВАНИЮ | ИЛЬИН АРТЁМ АЛЕКСАНДРОВИЧ | ВАРИАНТ №3" << '\n';
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
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
    app::print_main_menu();
    auto res = app::get_user_input("Введите что-то");
    std::cout << res;

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

void app::print_main_menu() {
    system("cls");
    std::cout
        << "________________________________" << '\n'
        << "Опции:" << '\n'
        << "1. Добавить запись" << '\n'
        << "2. Удалить запись" << '\n'
        << "3. Выборка по условию" << '\n'
        << "4. Сортировка по условию" << '\n'
        << "5. Печать таблицы" << '\n';
}

std::string app::get_user_input(std::string prompt) {
    std::cout 
        << "------" << '\n'
        << prompt << "> ";
    std::string res; std::cin >> res;
    return res;
}
