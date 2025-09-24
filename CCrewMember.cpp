#include "CCrewMember.h"
#include <iostream>
#include <string>
using namespace std;

// Helper function
bool CCrewMember::isValidName(const string& name) const
{
    return !name.empty();
}

// Constructor with validation
CCrewMember::CCrewMember(const string& name, int airMinutes)
    : name(""), airTime(0)
{
    setName(name);
    updateMinutes(airMinutes);
}

// Copy Constructor
CCrewMember::CCrewMember(const CCrewMember& other)
    : name(other.name), airTime(other.airTime)
{
}

// Destructor
CCrewMember::~CCrewMember()
{
}

// Update air minutes with validation
bool CCrewMember::updateMinutes(int minutes)
{
    if (minutes < 0) {
        return false;
    }
    this->airTime += minutes;
    return true;
}

// Getters and Setters
const string& CCrewMember::getName() const
{
    return name;
}

void CCrewMember::setName(const string& newName)
{
    if (isValidName(newName)) {
        this->name = newName;
    }
    // If invalid, don't change the name
}

int CCrewMember::getAirTime() const
{
    return airTime;
}

// Print - basic implementation that can be overridden
void CCrewMember::print() const
{
    cout << "Crewmember " << this->name << " minutes " << this->airTime << endl;
}

// Print with ostream parameter - basic implementation that can be overridden
void CCrewMember::print(ostream& os) const
{
    os << "Crewmember " << this->name << " minutes " << this->airTime << endl;
}

// Compare by name (base implementation)
bool CCrewMember::isEqual(const CCrewMember& other) const
{
    return name == other.name;
}

//Operations Functions
ostream& operator<<(ostream& os, const CCrewMember& crewMember)
{
    os << "Crewmember " << crewMember.name << " minutes " << crewMember.airTime << endl;
    return os;
}

bool CCrewMember::operator==(const CCrewMember& other) const
{
    return isEqual(other);
}

CCrewMember& CCrewMember::operator=(const CCrewMember& other)
{
    if (this != &other) { // protect against self-assignment
        name = other.name;
        airTime = other.airTime;
    }
    return *this; // allow chaining
}

// Virtual method implementation
bool CCrewMember::updateTime(int minutes)
{
    return updateMinutes(minutes);
}

// Modify the += operator to use the virtual method
bool CCrewMember::operator+=(const int updatedAirMinutes)
{
    return updateTime(updatedAirMinutes);
}