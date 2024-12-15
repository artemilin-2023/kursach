#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#ifndef KURSACH_STUDENT_H
#define KURSACH_STUDENT_H

#include <string>
#include <iostream>
#include <functional>

using std::string;

namespace database {
    namespace entities {
        class student {
        public:
            string firstName;
            string lastName;
            string patronymic;
            string dateOfBirth;
            string group;
            string address;
            string examResult;

            student();

            student(
                string firstName,
                string lastName,
                string patronymic,
                string dateOfBirth,
                string group,
                string address,
                string examResult
            );

            friend std::ostream& operator<<(std::ostream& os, const student& s);
        };
    }
}

#endif

#pragma clang diagnostic pop