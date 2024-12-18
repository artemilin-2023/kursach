// kursach.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <set>

#include "database.h"
#include "student.h"
#include "console_table.h"
#include "kursach.h"


using database::entities::student;
using ConsoleTable = samilton::ConsoleTable;

const std::vector<std::string> headers = { "i", "FIRST NAME", "LAST NAME", "PATRONYMIC", "DATE OF BIRTH", "GROUP", "ADDRESS", "EXAM RESULT" };
//const int sleepTime = 600;

int main()
{
    setlocale(LC_ALL, "");
    std::cout << "КУРСАВАЯ РАБОТА ПО ПРОГРАММИРОВАНИЮ | ИЛЬИН АРТЁМ АЛЕКСАНДРОВИЧ | ВАРИАНТ №3" << '\n';
    
    app::run();
    
    system("pause");
    return 0;
}

void app::run() {
    
    auto database = database::database<student>("data.db");
    
    while (true) {

        app::print_main_menu();
        auto user_input = app::get_user_input("выберите действие");

       while (!app::is_exist_command(user_input)) {
            std::cout << "Введенной команды не существует. Выберите команду из предложенных (ввод должен быть целым числом)." << '\n';
            continue;
       }

        auto command = std::atoi(user_input.c_str());
        if (command == -1) // exit from program
            break;

        auto handler = get_handler_for_command(command);
        handler(database);
    }
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
    std::cout
        << "________________________________" << '\n'
        << "Опции:" << '\n'
        << "1.  Добавить записи" << '\n'
        << "2.  Удалить запись" << '\n'
        << "3.  Выборка по условию" << '\n'
        << "4.  Сортировка по условию" << '\n'
        << "5.  Печать таблицы" << '\n'
        << "-1. Выход" << '\n';
}

std::string app::get_user_input(std::string prompt) {
    std::cout 
        << "------" << '\n'
        << prompt << "> ";
    std::string res; std::cin >> res;
    return res;
}

bool app::is_exist_command(string command) {
    auto commands = std::set<string>{ "1", "2", "3", "4", "5", "-1" };
    return commands.contains(command);
}

std::function<void(database::database<student>)> app::get_handler_for_command(int command) {
    switch (command)
    {
    case 1:
        return app::add_record_handler;
    case 2:
        return app::delete_record_handler;
    case 3:
        return app::selection_handler;
    case 4:
        return app::filtration_handler;
    case 5:
        return app::print_table_handler;
    }
}

void app::add_record_handler(database::database<student> db) {

}

void app::delete_record_handler(database::database<student> db) {

}

void app::selection_handler(database::database<student> db) {

}

void app::filtration_handler(database::database<student> db) {

}

void app::print_table_handler(database::database<student> db) {

}
