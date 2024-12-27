#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>

struct Person {
    Person(const std::string& name, const std::time_t birthday) : name(name), birthday(birthday) {}
    Person() : name(), birthday() {}
    std::string name;
    std::time_t birthday{};
};

Person getNextPerson(const std::vector<Person> &persons) {
    const auto t = std::time(nullptr);
    Person nextPerson;
    for (const auto &[name, birthday] : persons) {
        if (nextPerson.name.empty()) {
            nextPerson.birthday = birthday;
            nextPerson.name = name;
        }
        if (birthday > t) {
            if (nextPerson.birthday > birthday) {
                nextPerson.birthday = birthday;
                nextPerson.name = name;
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
        const auto in = std::localtime(&t);
        std::cin >> std::get_time(in, "%Y/%m/%d");
        newPerson.birthday = std::mktime(in);
        persons.push_back(newPerson);
    }
    const auto [name, birthday] = getNextPerson(persons);
    std::cout << "Name: " << name << std::endl;
    std::cout << "Birthday: " << std::put_time(std::localtime(&birthday), "%Y/%m/%d") << std::endl;
    return 0;
}