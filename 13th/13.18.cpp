#include <string>
#include <iostream>
using namespace std;

class Employee
{
private:
    /* data */
public:
    Employee(string name) name(name), id(id_last++){};
    Employee(const &Employee s) : name(s.name), id(id_last++) {}
    ~Employee();
    int id;
    string name;
    static int id_last;
};

int Employee::id_last = 0;