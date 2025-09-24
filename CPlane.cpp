#include "CPlane.h"
#include <iostream>
#include <string>
#include "CCargo.h"

using namespace std;

int CPlane::nextSerial = 100;

// Helper functions
bool CPlane::isValidString(const string& str) const
{
	return !str.empty();
}

bool CPlane::isValidPositiveInt(int value) const
{
	return value >= 0;
}

bool CPlane::isValidPositiveFloat(float value) const
{
	return value >= 0.0f;
}

// Constructor
CPlane::CPlane(int count, const string& name)
	:serialNumber(nextSerial++),
	modelName("Unknown Model"),
	seatCount(0)
{
	setModelName(name);
	setSeatCount(count);
}

// Copy Constructor
CPlane::CPlane(const CPlane& other)
	: serialNumber(other.serialNumber),
	modelName(other.modelName),
	seatCount(other.seatCount)
{

}

// Setters
void CPlane::setModelName(const string& name)
{
	if (isValidString(name)) {
		modelName = name;
	}
	// If invalid, don't change the model name
}

void CPlane::setSeatCount(int count)
{
	if (isValidPositiveInt(count)) {
		seatCount = count;
	}
	// If invalid, don't change the seat count
}

// Getters
int CPlane::getSerialNumber() const
{
	return serialNumber;
}

const string& CPlane::getModelName() const
{
	return modelName;
}

int CPlane::getSeatCount() const
{
	return seatCount;
}

// Functions
bool CPlane::isEqual(const CPlane& other) const
{
	return  serialNumber == other.serialNumber;
}

void CPlane::print(ostream& os) const
{
	os << "Plane " << serialNumber
		<< " degem " << modelName
		<< " seats " << seatCount << endl;
}

//Operations Functions
ostream& operator<<(ostream& os, const CPlane& plane)
{
    plane.print(os);  // Pass the ostream to the virtual print method
    return os;
}


bool CPlane::operator==(const CPlane& other) const
{
	return isEqual(other);
}

bool CPlane::operator!=(const CPlane& other)const
{
	return !isEqual(other);
}

CPlane& CPlane::operator=(const CPlane& other)
{
	if (this != &other) { // protect against self-assignment
		serialNumber = other.serialNumber;
		modelName = other.modelName;
		seatCount = other.seatCount;
	}
	return *this; // allow chaining
}

CPlane& CPlane::operator++()
{
	++seatCount;
	return *this;
}

CPlane CPlane::operator++(int)
{
	CPlane temp = *this;
	++seatCount;
	return temp;
}

CPlane::~CPlane()
{
}