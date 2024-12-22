// kursach.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <set>
#include <exception>

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
            user_input = app::get_user_input("выберите действие");
            continue;
       }

        auto command = std::atoi(user_input.c_str());
        if (command == -1) // exit from program
            break;

        if (command == 6) {
            app::clear_console();
            continue;
        }

        auto handler = get_handler_for_command(command);
        handler(&database);
    }
}

void app::print_table(std::vector<std::string> headers, database::core::list::linked_list<student>* data) {
    std::setlocale(LC_ALL, "C");

    ConsoleTable table(2, 2, samilton::Alignment::centre);
    table.addRow(headers);

    int i = 0;
    auto current = data->begin();
    do {
        if (current == nullptr) {
            std::cout << "В таблице нет ни одной записи." << '\n';
            break;
        }

        auto student = current->data;
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

        i++;
        current = current->next;
    } while (current != data->begin());

    std::cout << table;
    std::setlocale(LC_ALL, "");
}

void app::clear_console() {
    system("CLS");
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
        << "6.  Отчистить консоль" << '\n'
        << "-1. Выход" << '\n';
}

std::string app::get_user_input(std::string prompt) {
    std::cout
        << prompt << "> ";
    std::string res;
    std::getline(std::cin, res, '\n');
    return res;
}

bool app::is_exist_command(string command) {
    auto commands = std::set<string>{ "1", "2", "3", "4", "5", "6", "-1" };
    return commands.contains(command);
}

std::function<void(database::database<student>*)> app::get_handler_for_command(int command) {
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

void app::add_record_handler(database::database<student> *db) {
    auto useManualInput = app::get_user_input("осуществлять ручной ввод? (Y/y - да)");
    if (useManualInput == "Y" || useManualInput == "y" || useManualInput == "")
        app::add_record_by_manual_input(db);
    else
        app::add_record_from_file(db);

}

void app::add_record_by_manual_input(database::database<student>* db) {
    auto firstName = app::get_user_input("введите имя");
    auto lastName = app::get_user_input("введите фамилию");
    auto patronymic = app::get_user_input("введите отчество");
    auto dateOfBirth = app::get_user_input("введите дату рождения");
    auto group = app::get_user_input("введите номер группы");
    auto address = app::get_user_input("введите адрес проживания");
    auto examResult = app::get_user_input("введите результаты сессии (есть долги/нет долгов)");

    auto newStudent = student(firstName, lastName, patronymic, dateOfBirth, group, address, examResult);

    db->startTransaction();
    db->add(newStudent);
    db->commitTransaction();
}

void app::add_record_from_file(database::database<student>* db) {
    auto path = app::get_user_input("введите путь до файла с данными");
    std::fstream file_input(path);

    if (!file_input.good() || file_input.peek() == EOF) {
        std::cout << "Не удалось считать данные из указанного файла. Убедитесь, что файл по указанному пути существует и он не пуст." << '\n';
        return;
    }

    std::string line;
    int recordCounter = 0;
    db->startTransaction();
    while (std::getline(file_input, line))
    {
        auto entityData = helpers::parse_row(line, database::columnDelimiter);
        auto entity = helpers::map(entityData);
        db->add(entity);
        recordCounter += 1;
    }
    db->commitTransaction();
    std::cout << "Успешно добавлено " << recordCounter << " записей." << '\n';
}

void app::delete_record_handler(database::database<student> *db) {
    auto input = app::get_user_input("индекс для удаления");

    if (!is_number(input)) {
        std::cout << "Индекс должен быть целым числом." << '\n';
        return;
    }
    int index = atoi(input.c_str());

    db->startTransaction();
    db->deleteBy(index);
    db->commitTransaction();
}

bool app::is_number(const std::string& s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void app::selection_handler(database::database<student> *db) {
    std::cout << "Возможные поля для выборки: " << '\n';
    for (int i = 1; i < headers.size(); i++) {
        std::cout << " " << i << ". " << headers[i] << '\n';
    }

    auto input = app::get_user_input("введите номер поля");
    if (!is_number(input)) {
        std::cout << "Номер поля должен быть целым числом." << '\n';
        return;
    }

    auto field = atoi(input.c_str());
    if (field < 1 || field > headers.size()) {
        std::cout << "Некорректный номер поля." << '\n';
        return;
    }

    auto key = app::get_user_input("введите критерий выборки (" + headers[field] + " == your_key)");
    auto selector = app::get_selector_by_field(field, key);

    auto selectionResult = db->selectBy(selector);
    app::print_table(headers, selectionResult);
}

std::function<bool(const student&)> app::get_selector_by_field(int field, std::string key) {
    switch (field)
    {
    case 1:
        return [key](const student& s) {
            return s.firstName == key;
            };
    case 2:
        return [key](const student& s) {
            return s.lastName == key;
            };
    case 3:
        return [key](const student& s) {
            return s.patronymic == key;
            };
    case 4:
        return [key](const student& s) {
            return s.dateOfBirth == key;
            };
    case 5:
        return [key](const student& s) {
            return s.group == key;
            };
    case 6:
        return [key](const student& s) {
            return s.address == key;
            };
    case 7:
        return [key](const student& s) {
            return s.examResult == key;
            };
    }
}

void app::filtration_handler(database::database<student> *db) {
    std::cout << "Возможные поля для сортировки: " << '\n';
    for (int i = 1; i < headers.size(); i++) {
        std::cout << " " << i << ". " << headers[i] << '\n';
    }

    auto input = app::get_user_input("введите номер поля");
    if (!is_number(input)) {
        std::cout << "Номер поля должен быть целым числом." << '\n';
        return;
    }

    auto field = atoi(input.c_str());
    if (field < 1 || field > headers.size()) {
        std::cout << "Некорректный номер поля." << '\n';
        return;
    }

    auto comparater = app::get_comparator_by_field(field);
    auto sorted = db->orderBy(comparater);
    app::print_table(headers, sorted);
}

std::function<bool(const student&, const student&)> app::get_comparator_by_field(int field) {
    switch (field) {
    case 1:
        return [](const student& s1, const student& s2) {
            if (s1.firstName > s2.firstName)
                return 1;
            else if (s1.firstName == s2.firstName)
                return 0;
            return -1;
            };
    }
}

void app::print_table_handler(database::database<student> *db) {
    std::cout << "Текущие записи в бд:" << '\n';
    app::print_table(headers, db->getAll());
}
