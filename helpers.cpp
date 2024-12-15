#include "helpers.h"

student map(std::vector<std::string> data) {
    return student(data[0], data[1], data[2], data[3], data[4], data[5], data[6]);
}

std::vector<std::string> map(student entity) {
    return {
        entity.firstName,
        entity.lastName,
        entity.patronymic,
        entity.dateOfBirth,
        entity.group,
        entity.address,
        entity.examResult
    };
}

std::vector<std::string> parse_row(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}
