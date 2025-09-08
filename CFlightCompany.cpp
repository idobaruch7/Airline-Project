#include "CFlightCompany.h"
#include <iostream>

using namespace std;

// Helper function
bool CFlightCompany::isValidName(const string& name) const
{
	return !name.empty();
}

// Helper function to find flight by flight number
CFlight* CFlightCompany::getFlightByNumber(int flightNumber)
{
	for (int i = 0; i < flightCount; i++) {
		if (flights[i] != nullptr && 
			flights[i]->getFlightInfo().getFlightNumber() == flightNumber) {
			return flights[i];
		}
	}
	return nullptr; // Flight not found
}

// Helper function to find crew member by employee number
CCrewMember* CFlightCompany::getCrewMemberByNumber(int employeeNumber)
{
	// Note: Since CCrewMember doesn't have an employee number field in the signature,
	// I'm assuming we need to use a different identifier. 
	// For now, I'll use the crew member's position in the array as the employee number
	if (employeeNumber >= 0 && employeeNumber < crewCount && 
		crewMembers[employeeNumber] != nullptr) {
		return crewMembers[employeeNumber];
	}
	return nullptr; // Crew member not found
}

CFlightCompany::CFlightCompany(const string& name)
	: companyName(""), crewCount(0), planeCount(0), flightCount(0)
{
	// Initialize pointer arrays to nullptr
	for (int i = 0; i < MAX_CREWS; i++) {
		crewMembers[i] = nullptr;
	}
	for (int i = 0; i < MAX_PLANES; i++) {
		planes[i] = nullptr;
	}
	for (int i = 0; i < MAX_FLIGHT; i++) {
		flights[i] = nullptr;
	}
	
	setName(name);
}

CFlightCompany::CFlightCompany(const CFlightCompany& other)
	: companyName(other.companyName), crewCount(other.crewCount), 
	  planeCount(other.planeCount), flightCount(other.flightCount)
{
	// Initialize all arrays to nullptr first
	for (int i = 0; i < MAX_CREWS; i++) {
		crewMembers[i] = nullptr;
	}
	for (int i = 0; i < MAX_PLANES; i++) {
		planes[i] = nullptr;
	}
	for (int i = 0; i < MAX_FLIGHT; i++) {
		flights[i] = nullptr;
	}

	// Copy crew members (create new copies)
	for (int i = 0; i < crewCount; i++) {
		if (other.crewMembers[i] != nullptr) {
			crewMembers[i] = new CCrewMember(*other.crewMembers[i]);
		}
	}
	
	// Copy planes (create new copies)
	for (int i = 0; i < planeCount; i++) {
		if (other.planes[i] != nullptr) {
			planes[i] = new CPlane(*other.planes[i]);
		}
	}
	
	// Copy flights (create new copies)
	for (int i = 0; i < flightCount; i++) {
		if (other.flights[i] != nullptr) {
			flights[i] = new CFlight(*other.flights[i]);
		}
	}
}

void CFlightCompany::setName(const string& name)
{
	if (isValidName(name)) {
		companyName = name;
	}
	// If invalid, don't change the name
}

const string& CFlightCompany::getName() const
{
	return companyName;
}

bool CFlightCompany::addCrewMember(const CCrewMember& member)
{
	// Check if we've reached maximum capacity
	if (crewCount >= MAX_CREWS) {
		return false;
	}
	
	// Check if crew member already exists in the company
	for (int i = 0; i < crewCount; i++) {
		if (crewMembers[i] != nullptr && crewMembers[i]->isEqual(member)) {
			return false; // Crew member already exists
		}
	}
	
	// Add the crew member (create a copy)
	crewMembers[crewCount] = new CCrewMember(member);
	crewCount++;
	return true;
}

bool CFlightCompany::addPlane(const CPlane& plane)
{
	// Check if we've reached maximum capacity
	if (planeCount >= MAX_PLANES) {
		return false;
	}

	// Check if plane already exists in the company
	for (int i = 0; i < planeCount; i++) {
		if (planes[i] != nullptr && planes[i]->isEqual(plane)) {
			return false; // Plane already exists
		}
	}

	// Add the plane (create a copy)
	planes[planeCount] = new CPlane(plane);
	planeCount++;
	return true;
}

bool CFlightCompany::addFlight(const CFlight& flight)
{
	// Check if we've reached maximum capacity
	if (flightCount >= MAX_FLIGHT) {
		return false;
	}

	// Check if flight already exists in the company (compare by flight info)
	for (int i = 0; i < flightCount; i++) {
		if (flights[i] != nullptr &&
			flights[i]->getFlightInfo().isEqual(flight.getFlightInfo())) {
			return false; // Flight already exists
		}
	}

	// Add the flight (create a copy)
	flights[flightCount] = new CFlight(flight);
	flightCount++;
	return true;
}

bool CFlightCompany::addCrewToFlight(int employeeNumber, int flightNumber)
{
	// Find the flight by flight number
	CFlight* flight = getFlightByNumber(flightNumber);
	if (flight == nullptr) {
		return false; // Flight not found
	}
	
	// Find the crew member by employee number
	CCrewMember* crewMember = getCrewMemberByNumber(employeeNumber);
	if (crewMember == nullptr) {
		return false; // Crew member not found
	}
	
	// Add crew member to the flight
	return flight->addCrewMember(crewMember);
}

void CFlightCompany::print() const
{
	cout << "Flight company: " << companyName << endl;
}

CFlightCompany::~CFlightCompany()
{
	// Clean up dynamically allocated crew members
	for (int i = 0; i < crewCount; i++) {
		delete crewMembers[i];
	}
	
	// Clean up dynamically allocated planes
	for (int i = 0; i < planeCount; i++) {
		delete planes[i];
	}
	
	// Clean up dynamically allocated flights
	for (int i = 0; i < flightCount; i++) {
		delete flights[i];
	}
}

CPlane* CFlightCompany::getPlane(int index)
{
	// Validate index bounds
	if (index < 0 || index >= planeCount) {
		return nullptr; // Invalid index
	}
	
	// Return the plane at the specified index
	return planes[index];
}