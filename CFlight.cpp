#include "CFlight.h"
#include <iostream>

using namespace std;

// Helper functions
bool CFlight::isValidCrewIndex(int index) const
{
    return index >= 0 && index < crewCount;
}

int CFlight::findCrewMemberIndex(const CCrewMember& member) const
{
    for (int i = 0; i < crewCount; i++)
    {
        if (crewMembers[i] != nullptr && crewMembers[i]->isEqual(member))
        {
            return i;
        }
    }
    return -1; // Not found
}

// Constructors
CFlight::CFlight(const CFlightInfo& info)
    : flightInfo(info), assignedPlane(nullptr), crewCount(0)
{
    // Initialize crew array to nullptr
    for (int i = 0; i < MAX_CREW; i++)
    {
        crewMembers[i] = nullptr;
    }
}

CFlight::CFlight(const CFlightInfo& info, CPlane* plane)
    : flightInfo(info), assignedPlane(plane), crewCount(0)
{
    // Initialize crew array to nullptr
    for (int i = 0; i < MAX_CREW; i++)
    {
        crewMembers[i] = nullptr;
    }
}

CFlight::CFlight(const CFlight& other)
    : flightInfo(other.flightInfo), assignedPlane(other.assignedPlane), crewCount(other.crewCount)
{
    // Copy crew member pointers
    for (int i = 0; i < MAX_CREW; i++)
    {
        crewMembers[i] = other.crewMembers[i];
    }
}

// Destructor
CFlight::~CFlight()
{
    // Note: We don't delete crew members or plane as they are managed elsewhere
    // Just clear the pointers
    clearCrew();
    assignedPlane = nullptr;
}

// Plane management
void CFlight::setPlane(CPlane* plane)
{
    assignedPlane = plane;
}

CPlane* CFlight::getPlane() const
{
    return assignedPlane;
}

bool CFlight::hasPlane() const
{
    return assignedPlane != nullptr;
}

// Crew management
bool CFlight::addCrewMember(CCrewMember* member)
{
    if (member == nullptr || isCrewFull())
    {
        return false;
    }

    // Check if crew member is already on this flight
    if (findCrewMemberIndex(*member) != -1)
    {
        return false;
    }

    // Add crew member to the first available slot
    crewMembers[crewCount] = member;
    crewCount++;
    return true;
}

bool CFlight::removeCrewMember(const CCrewMember& member)
{
    int index = findCrewMemberIndex(member);
    if (index == -1)
    {
        return false;
    }
    return removeCrewMember(index);
}

bool CFlight::removeCrewMember(int index)
{
    if (!isValidCrewIndex(index))
    {
        return false;
    }

    // Shift remaining crew members down
    for (int i = index; i < crewCount - 1; i++)
    {
        crewMembers[i] = crewMembers[i + 1];
    }

    crewCount--;
    crewMembers[crewCount] = nullptr; // Clear the last slot
    return true;
}

int CFlight::getCrewCount() const
{
    return crewCount;
}

CCrewMember* CFlight::getCrewMember(int index) const
{
    if (isValidCrewIndex(index))
    {
        return crewMembers[index];
    }
    return nullptr;
}

bool CFlight::isCrewFull() const
{
    return crewCount >= MAX_CREW;
}

void CFlight::clearCrew()
{
    for (int i = 0; i < MAX_CREW; i++)
    {
        crewMembers[i] = nullptr;
    }
    crewCount = 0;
}

// Flight info access
const CFlightInfo& CFlight::getFlightInfo() const
{
    return flightInfo;
}

void CFlight::setFlightInfo(const CFlightInfo& info)
{
    flightInfo = info;
}

// Utility methods
void CFlight::print() const
{
    cout << "Flight Details:" << endl;
    cout << "  ";
    flightInfo.print();
    
    if (hasPlane())
    {
        cout << "  Assigned Plane: ";
        assignedPlane->print();
    }
    else
    {
        cout << "  Plane: UNASSIGNED" << endl;
    }

    cout << "  Crew Members (" << crewCount << "/" << MAX_CREW << "):" << endl;
    if (crewCount == 0)
    {
        cout << "    No crew assigned" << endl;
    }
    else
    {
        for (int i = 0; i < crewCount; i++)
        {
            cout << "    " << (i + 1) << ". ";
            if (crewMembers[i] != nullptr)
            {
                crewMembers[i]->print();
            }
        }
    }
}

// Operators
CFlight& CFlight::operator=(const CFlight& other)
{
    if (this != &other)
    {
        flightInfo = other.flightInfo;
        assignedPlane = other.assignedPlane;
        crewCount = other.crewCount;

        // Copy crew member pointers
        for (int i = 0; i < MAX_CREW; i++)
        {
            crewMembers[i] = other.crewMembers[i];
        }
    }
    return *this;
}

// REQUIRED OPERATORS - Adding the missing ones:

// Operator + for adding crew members
CFlight CFlight::operator+(CCrewMember* member) const
{
    CFlight result(*this);
    result.addCrewMember(member);
    return result;
}

// Operator == for comparison based on all flight parameters
bool CFlight::operator==(const CFlight& other) const
{
    // Compare flight info first
    if (!flightInfo.isEqual(other.flightInfo))
    {
        return false;
    }
    
    // Compare crew count
    if (crewCount != other.crewCount)
    {
        return false;
    }
    
    // Compare assigned plane
    if (assignedPlane == nullptr && other.assignedPlane == nullptr)
    {
        // Both have no plane assigned - this is equal
    }
    else if (assignedPlane == nullptr || other.assignedPlane == nullptr)
    {
        // One has a plane, the other doesn't - not equal
        return false;
    }
    else
    {
        // Both have planes assigned - compare them
        if (!assignedPlane->isEqual(*other.assignedPlane))
        {
            return false;
        }
    }
    
    // Compare crew members
    for (int i = 0; i < crewCount; i++)
    {
        // Check if both crew member pointers exist
        if (crewMembers[i] == nullptr || other.crewMembers[i] == nullptr)
        {
            // If one is null and the other isn't, they're not equal
            if (crewMembers[i] != other.crewMembers[i])
            {
                return false;
            }
        }
        else
        {
            // Both exist, compare the crew members
            if (!crewMembers[i]->isEqual(*other.crewMembers[i]))
            {
                return false;
            }
        }
    }
    
    // If we get here, all parameters are equal
    return true;
}

// The existing operator<< serves as the print operator (equivalent to operator>>)
ostream& operator<<(ostream& os, const CFlight& flight)
{
    // Print flight information
    os << "Flight " << flight.flightInfo.getFlightNumber() 
       << " to " << flight.flightInfo.getDest()
       << " (" << flight.flightInfo.getFlightTimeMinutes() << " minutes, " 
       << flight.flightInfo.getDistanceKM() << " km)";
    
    // Print plane information
    if (flight.hasPlane())
    {
        os << ", Plane: " << flight.assignedPlane->getModelName() 
           << " " << flight.assignedPlane->getSerialNumber()
           << " (Seats: " << flight.assignedPlane->getSeatCount() << ")";
    }
    else
    {
        os << ", No plane assigned";
    }
    
    // Print crew count
    os << ", Crew: " << flight.crewCount << "/" << MAX_CREW;
    
    return os;
}