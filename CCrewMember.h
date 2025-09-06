#pragma once

#include "CAddress.h"
#include <iostream>
#include <string>

using namespace std;

class CCrewMember {
private:
    string name;
    int airTime;
    CAddress address;

    bool isValidName(const string& name) const;

public:
    // Constructor (airMinutes default = 0)
    CCrewMember(const string& name, const CAddress& address, int airMinutes = 0);

    // Copy Constructor
    CCrewMember(const CCrewMember& other);

    // Destructor
    ~CCrewMember();

    // Update air minutes (adds minutes; return false if invalid input)
    bool updateMinutes(int minutes);

    // Get/Set name
    const string& getName() const;
    void setName(const string& newName);

    // Get/Set address
    const CAddress& getAddress() const;
    void setAddress(const CAddress& newAddress);

    // Get air time
    int getAirTime() const;

    // Print
    void print() const;

    // Compare by name
    bool isEqual(const CCrewMember& other) const;
};

