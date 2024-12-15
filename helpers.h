#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#ifndef KURSACH_HELPERS_H
#define KURSACH_HELPERS_H

#include "student.h"

#include <vector>
#include <string>
#include <sstream>

using database::entities::student;

namespace helpers {
    student map(std::vector<std::string> data);
    std::vector<std::string> map(student entity);

    std::vector<std::string> parse_row(std::string s, std::string delimiter);
}

#endif

#pragma clang diagnostic pop