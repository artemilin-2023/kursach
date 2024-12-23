#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#ifndef KURSACH_MAIN_H
#define KURSACH_MAIN_H

#include <string>
#include <vector>
#include "linked_list.h"
#include "student.h"

namespace app {

	// start up
	void run();
	

	// command handling
	bool is_exist_command(std::string command);
	std::function<void(database::database<student>*)> get_handler_for_command(int command);
	// database handlers
	void add_record_handler(database::database<student> *db);
	void delete_record_handler(database::database<student> *db);
	void selection_handler(database::database<student> *db);
	void filtration_handler(database::database<student> *db);
	void print_table_handler(database::database<student> *db);
	
	// helpers
	void print_table(std::vector<std::string> headers, database::core::list::linked_list<database::entities::student>* data);
	void print_main_menu();
	std::string get_user_input(std::string prompt);
	void add_record_by_manual_input(database::database<student>* db);
	void add_record_from_file(database::database<student>* db);
	bool is_number(const std::string& s);
	void clear_console();
	std::function<bool(const student&)> get_selector_by_field(int field, std::string key);
	std::function<int(const student&, const student&)> get_comparator_by_field(int field);
}


#endif

#pragma clang diagnostic pop
