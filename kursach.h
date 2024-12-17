#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#ifndef KURSACH_MAIN_H
#define KURSACH_MAIN_H

#include <string>
#include <vector>
#include "linked_list.h"
#include "student.h"

namespace app {

	void print_table(std::vector<std::string> headers, database::core::list::linked_list<database::entities::student>* data);
	void print_main_menu();
	std::string get_user_input(std::string prompt);
}


#endif

#pragma clang diagnostic pop
