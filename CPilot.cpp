#include "CPilot.h"
#include <iostream>
#include <cmath>

using namespace std;

// Constructor
CPilot::CPilot(const string& name, bool captain, CAddress* homeAddress, int airMinutes)
    : CCrewMember(name, airMinutes), isCaptain(captain), address(nullptr)
{
    if (homeAddress != nullptr) {
        address = new CAddress(*homeAddress);
    }
}

// Copy Constructor
CPilot::CPilot(const CPilot& other)
    : CCrewMember(other), isCaptain(other.isCaptain), address(nullptr)
{
    if (other.address != nullptr) {
        address = new CAddress(*other.address);
    }
}

// Destructor
CPilot::~CPilot()
{
    delete address;
    address = nullptr;
}

// Getters and Setters
bool CPilot::getIsCaptain() const
{
    return isCaptain;
}

void CPilot::setIsCaptain(bool captain)
{
    isCaptain = captain;
}

CAddress* CPilot::getAddress() const
{
    return address;
}

void CPilot::setAddress(CAddress* newAddress)
{
    delete address; // Clean up existing address
    address = nullptr;
    
    if (newAddress != nullptr) {
        address = new CAddress(*newAddress);
    }
}

bool CPilot::hasAddress() const
{
    return address != nullptr;
}

// Virtual method implementations
void CPilot::receivePresent() const
{
    cout << name << " thanking the company for receiving the holiday gift." << endl;
}

void CPilot::receiveUniform() const
{
    cout << name << " this is the fifth time I get a new uniform, this is a waste of money!" << endl;
}

void CPilot::updateFlightTime(int flightTimeMinutes)
{
    int timeToAdd = flightTimeMinutes;
    
    // If captain, add 10% bonus (rounded down)
    if (isCaptain) {
        int bonus = static_cast<int>(flightTimeMinutes * 0.1);
        timeToAdd += bonus;
    }
    
    updateMinutes(timeToAdd);
}

bool CPilot::isEqual(const CCrewMember& other) const
{
    // First check if names are equal
    if (!CCrewMember::isEqual(other)) {
        return false;
    }
    
    // Try to cast to CPilot to compare addresses
    const CPilot* otherPilot = dynamic_cast<const CPilot*>(&other);
    if (otherPilot == nullptr) {
        return false; // Different types
    }
    
    // Compare addresses
    if (address == nullptr && otherPilot->address == nullptr) {
        return true; // Both have no address
    }
    
    if (address == nullptr || otherPilot->address == nullptr) {
        return false; // One has address, other doesn't
    }
    
    return *address == *otherPilot->address;
}

void CPilot::print() const
{
    cout << "Pilot " << name << " minutes " << airTime;
    if (hasAddress()) {
        cout << " Address: ";
        address->print();
    } else {
        cout << " No address" << endl;
    }
    if (isCaptain) {
        cout << " Captain\n";
    }
    else
    {
        cout << " Not a Captain\n";
    }
}

void CPilot::print(ostream& os) const
{
    os << "Pilot " << name << " minutes " << airTime;
    if (isCaptain) {
        os << " a Captain";
    }
    else
    {
        os << " \nNot a Captain";
    }

    if (hasAddress()) {
        os << " Home ";
        os << *address;
    } else {
        os << " No address" << endl;
    }
}

// Pilot specific methods
void CPilot::goToSimulator() const
{
    cout << "Pilot " << name << " got the message will come soon" << endl;
}

// Assignment operator
CPilot& CPilot::operator=(const CPilot& other)
{
    if (this != &other) {
        CCrewMember::operator=(other);
        isCaptain = other.isCaptain;
        
        // Handle address assignment
        delete address;
        address = nullptr;
        
        if (other.address != nullptr) {
            address = new CAddress(*other.address);
        }
    }
    return *this;
}

// Override the virtual updateTime method to use updateFlightTime
bool CPilot::updateTime(int minutes)
{
    updateFlightTime(minutes); // This includes captain bonus logic
    return true;
}
