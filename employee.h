// Include the header file
//
//
//  STUFF GOES HERE
//
//
#ifndef _EMPLOYEE_H_
#define _EMPLOYEE_H_

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

const int MAXID = 9999;

class Employee {
   friend ostream& operator<<(ostream &, const Employee &);

public:
    Employee(string = "dummyLast", string = "dummyFirst", int = 0, int = 0);
    Employee(const Employee&); // copy constructor
    ~Employee();

    bool setData(ifstream&); // fill object w/ data from file

    Employee& operator=(const Employee&);

    bool operator<(const Employee&) const;
    bool operator>(const Employee&) const;
    bool operator<=(const Employee&) const;
    bool operator>=(const Employee&) const;
    bool operator==(const Employee&) const;
    bool operator!=(const Employee&) const;

private:
    string lastName;  // an Employee's last name
    string firstName; // an Employee's first name
    int idNumber;     // an Employee's ID number
    int salary;       // an Employee's salary
};

#endif