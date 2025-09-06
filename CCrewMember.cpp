#include "CCrewMember.h"
#include "CAddress.h"
#include <iostream>
#include <string>
using namespace std;

// Helper function
bool CCrewMember::isValidName(const string& name) const {
    return !name.empty();
}

// Constructor with validation
CCrewMember::CCrewMember(const string& name, const CAddress& address, int airMinutes)
    : address(address) {
    if (isValidName(name)) {
        this->name = name;
    }
    else {
        this->name = "Unknown";
    }

    this->airTime = (airMinutes >= 0) ? airMinutes : 0;
}

// Copy Constructor
CCrewMember::CCrewMember(const CCrewMember& other)
    : name(other.name), address(other.address), airTime(other.airTime) {
}

// Destructor
CCrewMember::~CCrewMember() {
}

// Update air minutes with validation
bool CCrewMember::updateMinutes(int minutes) {
    if (minutes < 0) {
        return false;
    }
    this->airTime += minutes;
    return true;
}

// Getters and Setters
const string& CCrewMember::getName() const {
    return name;
}

void CCrewMember::setName(const string& newName) {
    if (isValidName(newName)) {
        this->name = newName;
    }
    // If invalid, don't change the name
}

const CAddress& CCrewMember::getAddress() const {
    return this->address;
}

void CCrewMember::setAddress(const CAddress& newAddress) {
    this->address = newAddress;
}

int CCrewMember::getAirTime() const {
    return this->airTime;
}

// Print
void CCrewMember::print() const {
    cout << "Crewmember " << this->name << " minutes " << this->airTime << endl;
}

// Compare by name
bool CCrewMember::isEqual(const CCrewMember& other) const {
    return this->name == other.name;
}