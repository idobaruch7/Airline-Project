#pragma once

#include "CAddress.h"
#include <iostream>
#include <string>

using namespace std;

class CCrewMember {
private:
    int member;
    string name;
    int airTime;
    CAddress address;

    bool isValidName(const string& name) const;


public:
    static int nextMember;

    //Default Constructor Deletion
    CCrewMember() = delete;

    // Constructor (airMinutes default = 0)
    CCrewMember(const string& name, const CAddress& address, int airMinutes = 0);

    // Constructor (no address)
    CCrewMember(const string& name, int airMinutes = 0);

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

    // Get member serial
    int getMember() const;

    // Get air time
    int getAirTime() const;

    // Print
    void print() const;

    // Compare by name
    bool isEqual(const CCrewMember& other) const;

    //Operations
    friend ostream& operator<<(ostream& os, const CCrewMember& flightInfo); //<<

    bool operator==(const CCrewMember& other) const;
    bool operator+=(const int updatedAirMinutes);

    CCrewMember& operator=(const CCrewMember& other);
};




