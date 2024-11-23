#include <string>
#include <utility>
#include <ostream>
using string = std::string;
class person
{

private:
    /* data */

    string name;
    int age;

    void print() const;

public:
    person() = default;

    person(std::string name, int age);
    virtual ~person() {}

     string get_name() const;
     int get_age() const;

    void set_name(const string &name);
    void set_age(const int &age);

    // 支持链式操作
    friend std::ostream &operator<<(std::ostream &os, const person &person);
};
