#include <iostream>
#include "class.h"
person::person(std::string name, int age) : name(std::move(name)), age(age) {}

void person::print() const
{
    std::cout << "name " << name << " age " << age << std::endl;
    return;
}
string person::get_name() const
{
    return name;
}

int person::get_age() const
{
    return age;
}

void person::set_name(const string &name)
{
    person::name = name;
    return;
}
void person::set_age(const int &age)
{
    person::age = age;
    return;
}
std::ostream &operator<<(std::ostream &out_put, const person &person)
{
    out_put << "this one is :" << person.get_name() << std::endl
            << "age is " << person.get_age();
    return out_put;
}