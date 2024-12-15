#include "student.h"

namespace database {
    namespace entities {

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
                << s.firstName << " | "
                << s.lastName << " | "
                << s.patronymic << " | "
                << s.dateOfBirth << " | "
                << s.group << " | "
                << s.address << " | "
                << s.examResult << " | ";

            return os;
        }
    }
}