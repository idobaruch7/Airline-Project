#include "CHost.h"
#include <iostream>

using namespace std;

// Constructor
CHost::CHost(const string& name, eHostType type, int airMinutes)
    : CCrewMember(name, airMinutes), hostType(type)
{
}

// Copy Constructor
CHost::CHost(const CHost& other)
    : CCrewMember(other), hostType(other.hostType)
{
}

// Destructor
CHost::~CHost()
{
}

// Getters and Setters
CHost::eHostType CHost::getHostType() const
{
    return hostType;
}

void CHost::setHostType(eHostType type)
{
    hostType = type;
}

// Virtual method implementations
void CHost::receivePresent() const
{
    cout << name << " thanking hte company for receiving the holiday gift. I wasn't expecting it" << endl;
}

void CHost::receiveUniform() const
{
    cout << "I think the new uniform is very nice!" << endl;
}

void CHost::updateFlightTime(int flightTimeMinutes)
{
    // Host gets the full flight time (no bonus like captain)
    updateMinutes(flightTimeMinutes);
}

void CHost::print() const
{
    cout << "Host " << name << " minutes " << airTime << " Type: ";
    switch (hostType) {
        case eRegular:
            cout << "Regular";
            break;
        case eSuper:
            cout << "Super";
            break;
        case eCalcelan:
            cout << "Calcelan";
            break;
    }
    cout << endl;
}

void CHost::print(ostream& os) const
{
    os << "Host ";
    switch (hostType) {
        case eRegular:
            os << "Regular";
            break;
        case eSuper:
            os << "Super";
            break;
        case eCalcelan:
            os << "Calcelan";
            break;
    }
    os << name << " minutes " << airTime << " Type: " << endl;
}

// Assignment operator
CHost& CHost::operator=(const CHost& other)
{
    if (this != &other) {
        CCrewMember::operator=(other);
        hostType = other.hostType;
    }
    return *this;
}
