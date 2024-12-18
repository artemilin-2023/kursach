#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#ifndef KURSACH_MAIN_H
#define KURSACH_MAIN_H

#include <string>
#include <vector>
#include "linked_list.h"
#include "student.h"

namespace app {
	void run();
	void print_table(std::vector<std::string> headers, database::core::list::linked_list<database::entities::student>* data);
	void print_main_menu();
	std::string get_user_input(std::string prompt);

	// command handling
	bool is_exist_command(std::string command);
	std::function<void(const database::database<student>)> get_handler_for_command(int command);
	// handlers
	void app::add_record_handler(database::database<student> db);
	void app::delete_record_handler(database::database<student> db);
	void app::selection_handler(database::database<student> db);
	void app::filtration_handler(database::database<student> db);
	void app::print_table_handler(database::database<student> db);
}


#endif

#pragma clang diagnostic pop
