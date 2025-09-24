#include "CFlightCompany.h"
#include <iostream>
#include "CPilot.h"
#include "CHost.h"

using namespace std;

// Helper function
bool CFlightCompany::isValidName(const string& name) const
{
	return !name.empty();
}

void CFlightCompany::initializeArrays()
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
}

//Helper Function For Calling Pilots To Simulator
void CFlightCompany::pilotsToSimulator() const
{
	for (int i = 0; i < crewCount; ++i) {
		if (crewMembers[i] != nullptr) {
			CPilot* pilot = dynamic_cast<CPilot*>(crewMembers[i]);
			if (pilot != nullptr) {
				cout << "Pilot " << pilot->getName()
					<< " must go to simulator." << endl;
			}
		}
	}
}

//Crew Presents
void CFlightCompany::crewGetPresent() const {
	for (int i = 0; i < crewCount; i++) {
		if (crewMembers[i] != nullptr) {
			crewMembers[i]->receivePresent(); // קריאה פולימורפית
		}
	}
}

// Crew Unifroms
void CFlightCompany::crewGetUniform() const
{
	for (int i = 0; i < crewCount; ++i) {
		if (crewMembers[i]) {
			crewMembers[i]->receiveUniform();   // קריאה פולימורפית
		}
	}
}

//Helper function to return counter for cargo
int CFlightCompany::getCargoCount()
{
	int cnt = 0;
	for (int i = 0; i < planeCount; ++i) {
		if (planes[i] && dynamic_cast<CCargo*>(planes[i]) != nullptr)
			++cnt;
	}
	return cnt;
}

// Helper function to find flight by flight number
CFlight* CFlightCompany::getFlightByNum(int flightNumber)
{
	for (int i = 0; i < flightCount; i++) {
		if (flights[i] != nullptr &&
			flights[i]->getFlightInfo().getFlightNumber() == flightNumber) {
			return flights[i];
		}
	}
	return nullptr; // Flight not found
}

// Helper function to find crew member by index
CCrewMember* CFlightCompany::getCrewMember(const int index)
{
	if (index < 0 || index >= crewCount)
		return nullptr;

	return crewMembers[index];
}

CFlightCompany::CFlightCompany(const string& name)
	: companyName(""), crewCount(0), planeCount(0), flightCount(0)
{
	// Initialize pointer arrays to nullptr
	initializeArrays();

	setName(name);
}

CFlightCompany::CFlightCompany(const CFlightCompany& other)
	: companyName(other.companyName), crewCount(other.crewCount),
	planeCount(other.planeCount), flightCount(other.flightCount)
{
	// Initialize all arrays to nullptr first
	initializeArrays();

	// Copy crew members (create new copies)
	for (int i = 0; i < crewCount; i++) {
		if (other.crewMembers[i] != nullptr) {
			// Check if it's a pilot or host and create the appropriate object
			if (const CPilot* pilot = dynamic_cast<const CPilot*>(other.crewMembers[i])) {
				crewMembers[i] = new CPilot(*pilot);
			}
			else if (const CHost* host = dynamic_cast<const CHost*>(other.crewMembers[i])) {
				crewMembers[i] = new CHost(*host);
			}
			else {
				// This shouldn't happen if all crew members are either pilots or hosts
				crewMembers[i] = nullptr;
			}
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
		if (crewMembers[i] != nullptr && *crewMembers[i] == (member)) {
			return false; // Crew member already exists
		}
	}

	// Add the crew member (create a copy)


	if (const CPilot* p = dynamic_cast<const CPilot*>(&member)) {
		crewMembers[crewCount] = new CPilot(*p);
	}
	else if (const CHost* h = dynamic_cast<const CHost*>(&member)) {
		crewMembers[crewCount] = new CHost(*h);
	}
	else {
		return false;
	}

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
		if (planes[i] != nullptr && *planes[i] == (plane)) {
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
			flights[i]->getFlightInfo() == (flight.getFlightInfo())) {
			return false; // Flight already exists
		}
	}

	// Add the flight (create a copy)
	flights[flightCount] = new CFlight(flight);
	flightCount++;
	return true;
}

bool CFlightCompany::addCrewToFlight(int flightNumber, int index)
{
	// Find the flight by flight number
	CFlight* flight = getFlightByNum(flightNumber);
	if (flight == nullptr) {
		return false; // Flight not found
	}

	// Find the crew member by employee number
	CCrewMember* crewMember = getCrewMember(index);
	if (crewMember == nullptr) {
		return false; // Crew member not found
	}

	// Add crew member to the flight
	return flight->addCrewMember(crewMember);
}

void CFlightCompany::print(ostream& os) const
{
	os << "Flight company: " << companyName << endl;

	// Print crew members
	os << "There are " << crewCount << " Crew members:" << endl;
	for (int i = 0; i < crewCount; i++) {
		if (crewMembers[i] != nullptr) {
			crewMembers[i]->print(); // This outputs directly to cout
		}
	}

	// Print planes
	os << "There are " << planeCount << " Planes:" << endl;
	for (int i = 0; i < planeCount; i++) {
		if (planes[i] != nullptr) {
			planes[i]->print(); // This outputs directly to cout
		}
	}

	// Print flights
	os << "There are " << flightCount << " Flights:" << endl;
	for (int i = 0; i < flightCount; i++) {
		if (flights[i] != nullptr) {
			flights[i]->print(); // This outputs directly to cout
		}
	}
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