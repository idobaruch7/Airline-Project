#include "CFlightCompany.h"
#include <iostream>

using namespace std;

// Helper function
bool CFlightCompany::isValidName(const string& name) const
{
	return !name.empty();
}

CFlightCompany::CFlightCompany(const string& name)
	: companyName("")
{
	setName(name);
}

CFlightCompany::CFlightCompany(const CFlightCompany& other)
	: companyName(other.companyName)
{
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

void CFlightCompany::print() const
{
	cout << "Flight company: " << companyName << endl;
}

CFlightCompany::~CFlightCompany()
{
}