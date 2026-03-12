#include "CHost.h"
#include <iostream>
#include <iomanip>

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
    cout << name << " thanking the company for receiving the holiday gift. I wasn't expecting it" << endl;
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
    print(cout);
}

void CHost::print(ostream& os) const
{
    os << left << setw(15) << name << " | " << setw(10) << "Host" << " | " << setw(10) << airTime << " | ";
    switch (hostType) {
        case eRegular:
            os << "Regular";
            break;
        case eSuper:
            os << "Super";
            break;
        case ePurser:
            os << "Purser";
            break;
    }
    os << "\n";
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
