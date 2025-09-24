#pragma once

#include "CAddress.h"
#include <iostream>
#include <string>

using namespace std;

class CCrewMember {
protected:
    string name;
    int airTime;

    bool isValidName(const string& name) const;

public:
    //Default Constructor Deletion
    CCrewMember() = delete;

    // Constructor (airMinutes default = 0)
    CCrewMember(const string& name, int airMinutes = 0);

    // Copy Constructor
    CCrewMember(const CCrewMember& other);

    // Virtual Destructor
    virtual ~CCrewMember();

    // Update air minutes (adds minutes; return false if invalid input)
    bool updateMinutes(int minutes);

    // Get/Set name
    const string& getName() const;
    void setName(const string& newName);

    // Get air time
    int getAirTime() const;

    // Pure virtual methods that derived classes must implement
    virtual void receivePresent() const = 0;
    virtual void receiveUniform() const = 0;
    virtual void updateFlightTime(int flightTimeMinutes) = 0;

    // Virtual methods that can be overridden
    virtual void print() const;
    virtual void print(ostream& os) const;
    virtual bool isEqual(const CCrewMember& other) const;

    //Operations
    friend ostream& operator<<(ostream& os, const CCrewMember& crewMember);

    bool operator==(const CCrewMember& other) const;
    bool operator+=(const int updatedAirMinutes);

    CCrewMember& operator=(const CCrewMember& other);

    // Make a virtual method for updating time
    virtual bool updateTime(int minutes);
};




