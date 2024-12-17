#include "student.h"
#include <iomanip>

namespace database {
    namespace entities {

        const int outputWidth = 7;

        student::student() { }

        student::student(
            string firstName,
            string lastName,
            string patronymic,
            string dateOfBirth,
            string group,
            string address,
            string examResult) 
        {
            this->firstName = firstName;
            this->lastName = lastName;
            this->patronymic = patronymic;
            this->dateOfBirth = dateOfBirth;
            this->group = group;
            this->address = address;
            this->examResult = examResult;
        }

        std::ostream& operator<<(std::ostream& os, const student& s) {
            os << " | "
                << std::setw(outputWidth)  << s.firstName << std::setw(outputWidth) << " | "
                << std::setw(outputWidth)  << s.lastName << std::setw(outputWidth) << " | "
                << std::setw(outputWidth)  << s.patronymic << std::setw(outputWidth) << " | "
                << std::setw(outputWidth)  << s.dateOfBirth << std::setw(outputWidth) << " | "
                << std::setw(outputWidth)  << s.group << std::setw(outputWidth) << " | "
                << std::setw(outputWidth)  << s.address << std::setw(outputWidth) << " | "
                << std::setw(outputWidth)  << s.examResult << std::setw(outputWidth) << " | ";

            return os;
        }
    }
}