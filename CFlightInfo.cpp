#include "CFlightInfo.h"
#include <iostream>

using namespace std;

// Helper functions
bool CFlightInfo::isValidString(const string& str) const
{
	return !str.empty();
}

bool CFlightInfo::isValidPositiveInt(int value) const
{
	return value >= 0;
}

// Constructors
CFlightInfo::CFlightInfo(const string& dest, int number, int timeMinutes, int distance)
	: flightNumber(0),
	destination("Unknown Destination"),
	flightTimeMinutes(0),
	distanceKM(0)
{
	setFlightNumber(number);
	setDest(dest);
	setFlightTimeMinutes(timeMinutes);
	setDistanceKM(distance);
}

CFlightInfo::CFlightInfo(const CFlightInfo& other)
	: flightNumber(other.flightNumber),
	destination(other.destination),
	flightTimeMinutes(other.flightTimeMinutes),
	distanceKM(other.distanceKM)
{
}

// Setters
void CFlightInfo::setFlightNumber(int number)
{
	if (isValidPositiveInt(number)) {
		flightNumber = number;
	}
	// If invalid, don't change the flight number
}

void CFlightInfo::setDest(const string& dest)
{
	if (isValidString(dest)) {
		destination = dest;
	}
	// If invalid, don't change the destination
}

void CFlightInfo::setFlightTimeMinutes(int timeMinutes)
{
	if (isValidPositiveInt(timeMinutes)) {
		flightTimeMinutes = timeMinutes;
	}
	// If invalid, don't change the flight time
}

void CFlightInfo::setDistanceKM(int distance)
{
	if (isValidPositiveInt(distance)) {
		distanceKM = distance;
	}
	// If invalid, don't change the distance
}

// Getters
int CFlightInfo::getFlightNumber() const
{
	return flightNumber;
}

const string& CFlightInfo::getDest() const
{
	return destination;
}

int CFlightInfo::getFlightTimeMinutes() const
{
	return flightTimeMinutes;
}

int CFlightInfo::getDistanceKM() const
{
	return distanceKM;
}

// Functions
bool CFlightInfo::isEqual(const CFlightInfo& other) const
{
	return flightNumber == other.flightNumber;
}

void CFlightInfo::print() const
{
	cout << "Flight Info dest: " << destination
		<< " Number " << flightNumber
		<< " minutes " << flightTimeMinutes
		<< " KM " << distanceKM << endl;  // Make sure this has endl
}

//Operations Functions
ostream& operator<<(ostream& os, const CFlightInfo& flightInfo)
{
	os << "Flight Info dest: " << flightInfo.destination
		<< " Number " << flightInfo.flightNumber
		<< " minutes " << flightInfo.flightTimeMinutes
		<< " KM " << flightInfo.distanceKM << endl;

	return os; // allows chaining like cout >> a >> b;;
}

bool CFlightInfo::operator==(const CFlightInfo& other) const
{
	return isEqual(other);
}

bool CFlightInfo::operator!=(const CFlightInfo& other) const
{
	return !isEqual(other);
}

CFlightInfo& CFlightInfo::operator=(const CFlightInfo& other)
{

	if (this != &other) { // protect against self-assignment
		flightNumber = other.flightNumber;
		destination = other.destination;
		flightTimeMinutes = other.flightTimeMinutes;
		distanceKM = other.distanceKM;
	}

	return *this; // allow chaining
}


CFlightInfo::operator int() const
{
	return flightTimeMinutes;
}

// Destructor
CFlightInfo::~CFlightInfo()
{
}