// Include the header file
//
//
//  STUFF GOES HERE
//
//
#include "nodedata.h"

//----------------------------------------------------------------------------
// NodeData(int n, char c)
// Description: Default Constructor
// Defaults to int = 0, char = 'z' if nothing specified
NodeData::NodeData(int n, char c) {
    num = n;
    ch = c;
}

//----------------------------------------------------------------------------
// NodeData(const NodeData& other)
// Description: Copy Constructor
NodeData::NodeData(const NodeData& other) {
    num = other.num;
    ch = other.ch;
}

//----------------------------------------------------------------------------
// ~NodeData()
// Description: Destructor for NodeData (defined for clarity)
NodeData::~NodeData() { }

//----------------------------------------------------------------------------
// setData()
// Description: Takes user input to set the NodeData values
bool NodeData::setData() {
    cout << "Please enter an integer: ";
    cin >> num;
    cout << "Please enter a character: ";
    cin >> ch;
    return true;
}

//----------------------------------------------------------------------------
// setData(ifstream& infile)
// Description:  Takes data from file to set values of
//               NodeData member variables
bool NodeData::setData(ifstream& infile) {
    infile >> num;
    char tmp;
    infile >> tmp;
    ch = tmp;
    return true;
}

//----------------------------------------------------------------------------
// operator=
// Description: Passes the reference of a NodeData object to allow another
//              (left side/calling object) to copy it's contents
NodeData& NodeData::operator=(const NodeData& other) {
    num = other.num;
    ch = other.ch;
    return *this;
}

//----------------------------------------------------------------------------
// operator<
// Description: compares the num values first,
//              ch used if num values are equal
bool NodeData::operator<(const NodeData& other) const {
    if (num < other.num)
        return true;
    if (num == other.num)
        return ch < other.ch;
    return false;
}

//----------------------------------------------------------------------------
// operator>
// Description: compares the num values first,
//              ch used if num values are equal
bool NodeData::operator>(const NodeData& other) const {
    if (num > other.num)
        return true;
    if (num == other.num)
        return ch > other.ch;
    return false;
}

//----------------------------------------------------------------------------
// operator<=
// Description: Preforms the same way as operator< with the exception it
//              allows for equality too (using the == operator)
bool NodeData::operator<=(const NodeData& other) const {
    return (*this < other) || (*this == other);
}

//----------------------------------------------------------------------------
// operator>=
// Description: Preforms the same way as operator> with the exception it
//              allows for equality too (using the == operator)
bool NodeData::operator>=(const NodeData& other) const {
    return (*this > other) || (*this == other);
}

//----------------------------------------------------------------------------
// operator==
// Description: return true if num and ch of both NodeData are equal values
bool NodeData::operator==(const NodeData& other) const {
    return num == other.num && ch == other.ch;
}

//----------------------------------------------------------------------------
// operator!=
// Description: return true if either the num or ch of
//              both NodeData are not equal
bool NodeData::operator!=(const NodeData& other) const {
    return !(*this == other);
}

//----------------------------------------------------------------------------
// operator<<
// Description: returns the two data members, seperated with a space char
//              and ends with a new line character as opposed to an 'endl'
ostream& operator<<(ostream& output, const NodeData& other) {
    output << other.num << ' ' << /*(char)*/ other.ch << '\n';
    return output;
}