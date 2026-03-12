#pragma once
#include "CFlightInfo.h"
#include "CPlane.h"
#include "CCrewMember.h"
#include <iostream>
#include "CPilot.h"
#include "CHost.h"
#include "CCargo.h"

using namespace std;

class CFlight
{
private:
    static constexpr int MAX_CREW = 10; // Use constexpr for compile-time constant
    
    CFlightInfo flightInfo;        // The flight's data (contained by value)
    CPlane* assignedPlane;         // Pointer to assigned plane (can be nullptr initially)
    CCrewMember* crewMembers[MAX_CREW]; // Array of pointers to crew members
    int crewCount;                 // Current number of crew members

    // Helper functions
    bool isValidCrewIndex(int index) const;
    int findCrewMemberIndex(const CCrewMember& member) const;

public:
    // Constructors
    CFlight(const CFlightInfo& info);                    // Constructor with flight info only
    CFlight(const CFlightInfo& info, CPlane* plane);     // Constructor with flight info and plane
    CFlight(const CFlight& other);                       // Copy constructor

    CFlight() = delete;

    // Destructor
    ~CFlight();

    // Plane management
    void setPlane(CPlane* plane);    // Assign or change the plane (can be nullptr)
    CPlane* getPlane() const;        // Get assigned plane
    bool hasPlane() const;           // Check if plane is assigned

    // Crew management
    bool addCrewMember(CCrewMember* member);        // Add crew member to flight
    bool removeCrewMember(const CCrewMember& member); // Remove crew member from flight
    bool removeCrewMember(int index);               // Remove crew member by index
    int getCrewCount() const;                       // Get current crew count
    CCrewMember* getCrewMember(int index) const;    // Get crew member by index
    bool isCrewFull() const;                        // Check if crew is at maximum capacity
    void clearCrew();                               // Remove all crew members

    // Flight info access
    const CFlightInfo& getFlightInfo() const;       // Get flight information
    void setFlightInfo(const CFlightInfo& info);    // Update flight information

    // Utility methods
    void print() const;                             // Print flight details
    bool takeOff();

    // Operators
    CFlight& operator=(const CFlight& other);       // Assignment operator
    friend ostream& operator<<(ostream& os, const CFlight& flight); // Output operator
    CFlight& operator+(CCrewMember* member);  // Add crew member operator
    bool operator==(const CFlight& other) const;         // Comparison operator
};