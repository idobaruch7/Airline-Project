#pragma once
#include <string>
#include <iostream>
#include "CCrewMember.h"
#include "CPlane.h"
#include "CFlight.h"
#include "CCargo.h"

using namespace std;

// Constants for maximum array sizes
const int MAX_CREWS = 50;
const int MAX_PLANES = 20;
const int MAX_FLIGHT = 100;

class CFlightCompany
{
private:
	string companyName;

	// Array management variables - using pointers
	CCrewMember* crewMembers[MAX_CREWS];     // Array of crew member pointers
	CPlane* planes[MAX_PLANES];              // Array of plane pointers
	CFlight* flights[MAX_FLIGHT];            // Array of flight pointers

	int crewCount;                           // Current number of crew members
	int planeCount;                          // Current number of planes
	int flightCount;                         // Current number of flights

	bool isValidName(const string& name) const;

	// Helper functions
	void initializeArrays();

public:
	CFlightCompany(const string& name);
	CFlightCompany(const CFlightCompany& other);

	CFlightCompany() = delete;

	void setName(const string& name);
	const string& getName() const;

	bool addCrewMember(const CCrewMember& member);
	bool addPlane(const CPlane& plane);
	bool addFlight(const CFlight& flight);
	bool addCrewToFlight(int flightNumber, int employeeNumber);

	void crewGetUniform() const;
	void crewGetPresent() const;
	int getCargoCount();
	void pilotsToSimulator() const;
	CFlight* getFlightByNum(int flightNumber);
	CCrewMember* getCrewMember(const int index);

	CPlane* getPlane(int index);

	void print(ostream& os) const;

	~CFlightCompany();
};

