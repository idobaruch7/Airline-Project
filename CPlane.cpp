#include "CPlane.h"
#include <iostream>
#include <string>

using namespace std;

// Helper functions
bool CPlane::isValidString(const string& str) const
{
	return !str.empty();
}

bool CPlane::isValidPositiveInt(int value) const
{
	return value >= 0;
}

// Constructor
CPlane::CPlane(int number, int count, const string& name)
	: serialNumber(isValidPositiveInt(number) ? number : 0),
	modelName(isValidString(name) ? name : "Unknown Model"),
	seatCount(isValidPositiveInt(count) ? count : 0)
{
}

// Copy Constructor
CPlane::CPlane(const CPlane& other)
	: serialNumber(other.serialNumber),
	modelName(other.modelName),
	seatCount(other.seatCount)
{
}

// Setters
void CPlane::setSerialNumber(int number)
{
	if (isValidPositiveInt(number)) {
		serialNumber = number;
	}
	// If invalid, don't change the serial number
}

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
	return serialNumber == other.serialNumber;
}

void CPlane::print() const
{
	cout << "Plane " << serialNumber
		<< " degem " << modelName
		<< " seats " << seatCount << endl;
}

CPlane::~CPlane()
{
}