/
//  DBentry.cpp
//  
//
//  Created by Hee Seung Hong on 11/25/19.
//

//#include <stdio.h>

#include "DBentry.h"

// the default constructor
DBentry::DBentry(){
    // empty
}

// constructor
DBentry::DBentry (string _name, unsigned int _IPaddress, bool _active){
    name = _name;
    IPaddress = _IPaddress;
    active = _active;
}

// the destructor
DBentry::~DBentry(){
    // empty
}

// sets the domain name, which we will use as a key.
void DBentry::setName(string _name){
    name = _name;
}

// sets the IPaddress data.
void DBentry::setIPaddress(unsigned int _IPaddress){
    IPaddress = _IPaddress;
}

// sets whether or not this entry is active.
void DBentry::setActive (bool _active){
    active = _active;
}

// returns the name.
string DBentry::getName() const{
    return name;
}

// returns the IPaddress data.
unsigned int DBentry::getIPaddress() const{
    return IPaddress;
}

// returns whether or not this entry is active.
bool DBentry::getActive() const{
    return active;
}

// prints the entry in the format
// name : IPaddress : active  followed by newline
// active is printed as a string (active or inactive)
ostream& operator<< (ostream& out, const DBentry& rhs){
    string YorN_active;
    
    if(rhs.active){
        YorN_active = "active";
    }else{
        YorN_active = "inactive";
    }
    
    out << rhs.name << " : " << rhs.IPaddress << " : " << YorN_active;
    
    return out;
}
