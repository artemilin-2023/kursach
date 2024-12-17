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
}


#endif

#pragma clang diagnostic pop
