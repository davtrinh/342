// Include the header file
//
//
//  STUFF GOES HERE
//
//
#include "employee.h"

//----------------------------------------------------------------------------
// Employee(string last, string first, int id, int sal)
// Description: Default constructor for creating an employee
Employee::Employee(string last, string first, int id, int sal) {
    idNumber = (id >= 0 && id <= MAXID ? id : -1);
    salary = (sal >= 0 ? sal : -1);
    lastName = last;
    firstName = first;
}

//----------------------------------------------------------------------------
// Employee(const Employee& other)
// Description: Copy constructor
Employee::Employee(const Employee& other) {
    lastName = other.lastName;
    firstName = other.firstName;
    idNumber = other.idNumber;
    salary = other.salary;
}

//----------------------------------------------------------------------------
// ~Employee()
// Description: Employee destructor (defined for clarity)
Employee::~Employee() { }

//----------------------------------------------------------------------------
// setData(ifstream& inFile) {
// Description: sets an Employee's data from use of a file as input
bool Employee::setData(ifstream& InFile) {
    InFile >> lastName >> firstName >> idNumber >> salary;
    return idNumber >= 0 && idNumber <= MAXID && salary >= 0;
}

//----------------------------------------------------------------------------
// operator=
// Description: Employee assignment operator
//              (assign one Employee's contents to another)
Employee& Employee::operator=(const Employee& other) {
    if (&other != this) { // check for self assignment
        lastName = other.lastName;
        firstName = other.firstName;
        idNumber = other.idNumber;
        salary = other.salary;
    }
    return *this;
}

//----------------------------------------------------------------------------
// operator<
// Description: Compares the last names first, uses first names if the last
//              names are equal
bool Employee::operator<(const Employee& other) const {
    return lastName < other.lastName ||
        (lastName == other.lastName && firstName < other.firstName);
}

//----------------------------------------------------------------------------
// operator>
// Description: Compares the last names first, uses first names if the last
//              names are equal
bool Employee::operator>(const Employee& other) const {
    return lastName > other.lastName ||
        (lastName == other.lastName && firstName > other.firstName);
}

//----------------------------------------------------------------------------
// operator<=
// Description: Preforms the same as operator< with the exception that
//              this allows for equality
bool Employee::operator<=(const Employee& other) const {
    return *this < other || *this == other;
}

//----------------------------------------------------------------------------
// operator>=
// Description: Preforms the same as operator> with the exception that
//              this allows for equality
bool Employee:: operator>=(const Employee& other) const {
    return *this > other || *this == other;
}

//----------------------------------------------------------------------------
// operator==
// Description: tests both Employee objects for equality based off of NAME
//              only, (first and last).
// [Already typed]: if name of calling and passed object are equal,
//                  return true, otherwise false
bool Employee::operator==(const Employee& other) const {
    return lastName == other.lastName && firstName == other.firstName;
}

//----------------------------------------------------------------------------
// operator!=
// Description: returns the opposide value of operator==, testing true if both Employee
// objects' first and last names do not match.
bool Employee::operator!=(const Employee& other) const {
    return !(*this == other);
}

//----------------------------------------------------------------------------
// operator<<
// display an Employee object / return to ostream&
ostream& operator<<(ostream& output, const Employee& displayEmployee) {
    output << setw(4) << displayEmployee.idNumber << setw(7) <<
        displayEmployee.salary << " " << displayEmployee.lastName <<
        " " << displayEmployee.firstName << endl;
    return output;
}