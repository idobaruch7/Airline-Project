#include "CCrewMember.h"
#include "CAddress.h"
#include <iostream>
#include <string>
using namespace std;

int CCrewMember::nextMember = 1000;

// Helper function
bool CCrewMember::isValidName(const string& name) const
{
    return !name.empty();
}

// Constructor with validation
CCrewMember::CCrewMember(const string& name, const CAddress& address, int airMinutes)
    : name(""), address(address), airTime(0), member(nextMember++)
{
    setName(name);
    updateMinutes(airMinutes);
}

// Constructor (no address)
CCrewMember::CCrewMember(const string& name, int airMinutes) : name(""), member(nextMember++), address(0, "Unknown Street")
{
    this->airTime = (airMinutes >= 0) ? airMinutes : 0;
    setName(name);
}

// Copy Constructor
CCrewMember::CCrewMember(const CCrewMember& other)
    : name(other.name), address(other.address), airTime(other.airTime), member(other.member)
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

const CAddress& CCrewMember::getAddress() const
{
    return this->address;
}

void CCrewMember::setAddress(const CAddress& newAddress)
{
    this->address = newAddress;
}

int CCrewMember::getMember() const
{
    return member;
}

int CCrewMember::getAirTime() const
{
    return airTime;
}

// Print
void CCrewMember::print() const
{
    cout << "Crewmember " << this->name << " minutes " << this->airTime << endl;
}

// Compare by name
bool CCrewMember::isEqual(const CCrewMember& other) const
{
    return member == other.member;
}

//Operations Functions
ostream& operator<<(ostream& os, const CCrewMember& crewMember)
{
    os << "Crewmember " << crewMember.name << " minutes " << crewMember.airTime << endl;
    return os; // allows chaining like cout >> a >> b;;
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
        member = other.member;
        address = other.address;

    }

    return *this; // allow chaining
}


bool CCrewMember::operator+=(const int updatedAirMinutes)
{
    return updateMinutes(updatedAirMinutes);
}