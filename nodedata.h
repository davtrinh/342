// Include the header file
//
//
//  STUFF GOES HERE
//
//
#ifndef NODEDATA_H
#define NODEDATA_H

#include <iostream>
#include <fstream>
using namespace std;

class NodeData {

   friend ostream& operator<<(ostream &, const NodeData &);
   // in stream operator ?

public:
    NodeData(int = 0, char = 'z'); // 2-param c'tor w/ default val's
    NodeData(const NodeData&); // copy c'tor  // added
	~NodeData();

    bool setData(); // set data via user prompt
    bool setData(ifstream&); // read data from file

    NodeData& operator=(const NodeData&); // added

    // operator<, operator> are defined by order of num
    // ex. 1 < 4 == true
    // if nums are equal, then ch is compared (as int values, same as num)
    bool operator<(const NodeData&) const;
    bool operator>(const NodeData&) const;
    bool operator<=(const NodeData&) const; // added
    bool operator>=(const NodeData&) const; // added
    bool operator==(const NodeData&) const;
    bool operator!=(const NodeData&) const;

private:
    int num;
    int ch;
};

#endif