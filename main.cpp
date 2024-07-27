//
// Created by vvv on 7/26/24.
//

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>

struct Person {
    std::string name;
    std::time_t birthday{};
};

Person getNextPerson(const std::vector<Person> &persons) {
    const auto t = std::time(nullptr);
    const auto *current = std::gmtime(&t);
    const auto currentMonth = current->tm_mon;
    const auto currentDay = current->tm_mday;
    Person nextPerson;
    for (const auto &[name, birthday] : persons) {
        const auto *tm = std::gmtime(&birthday);
        const auto birthMonth = tm->tm_mon;
        const auto birthDay = tm->tm_mday;
        if (birthMonth > currentMonth || (birthMonth == currentMonth && birthDay > currentDay)) {
            const auto buf = std::gmtime(&nextPerson.birthday);
            const auto bufMonth =  buf->tm_mon;
            const auto bufDay = buf->tm_mday;
            if (!nextPerson.name.empty() && birthMonth > bufMonth || (birthMonth == bufMonth && birthDay > bufDay)) {
                nextPerson.name = name;
                nextPerson.birthday = birthday;
            }
        }
    }
    return nextPerson;
}

int main() {
    std::vector<Person> persons;
    while (true) {
        Person newPerson;
        std::cout << "Enter the name of the person (or 'end' to quit): ";
        std::cin >> newPerson.name;

        if (newPerson.name == "end") { break; }

        std::cout << "Enter the date of birth (YYYY/MM/DD): ";
        const auto t = std::time(nullptr);
        const auto in = std::gmtime(&t);
        std::cin >> std::get_time(in, "%Y/%m/%d");
        newPerson.birthday = std::mktime(in);
        persons.push_back(newPerson);
    }
    const auto nextPerson = getNextPerson(persons);
    std::cout << "Name: " << nextPerson.name << std::endl;
    std::cout << "Birthday: " << std::put_time(std::gmtime(&nextPerson.birthday), "%m/%d") << std::endl;
    return 0;
}